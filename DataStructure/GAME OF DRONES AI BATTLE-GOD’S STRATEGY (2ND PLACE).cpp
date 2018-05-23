#include<iostream>
#include<iomanip>
#include<random>
#include<string>
#include<vector>
#include<list>
#include<set>
#include<cmath>
#include<algorithm>

const double M_PI = 3.141592653;

struct zone;
struct vec2
{
	int x, y;
	int turns2(vec2 target) const;
	int turns2(zone target) const;
	vec2(int x, int y) :x(x), y(y){}
	vec2(){}
};
vec2 operator-(vec2 a, vec2 b){ return{ a.x - b.x, a.y - b.y }; }
vec2 operator+(vec2 a, vec2 b){ return{ a.x + b.x, a.y + b.y }; }
vec2 operator/(vec2 a, float b){ return{ int(a.x / b), int(a.y / b) }; }
vec2 operator*(float b, vec2 a){ return{ int(a.x*b), int(a.y*b) }; }
vec2 operator*(vec2 a, float b){ return{ int(a.x*b), int(a.y*b) }; }
bool operator==(vec2 a, vec2 b){ return{ a.x == b.x && a.y == b.y }; }
bool operator<(vec2 a, vec2 b){ return{ a.x != b.x ? a.x < b.x : a.y < b.y }; }//for std::set
int det(vec2 a, vec2 b){ return a.x*b.y - a.y*b.x; }
int dot(vec2 a, vec2 b){ return a.x*b.x + a.y*b.y; }
float norm(vec2 a){ return std::sqrt(a.x*a.x + a.y*a.y); }
std::ostream& operator<<(std::ostream& out, const vec2& a){ return out << a.x << " " << a.y; }

struct zone
{
	vec2 pos;
	int owner_id;
	int id();
	zone(){}
};
struct drone
{
	int id;
	int player_id;
	vec2 pos = { -1, -1 };
	int turns2(vec2 target) const;
	int turns2(zone target) const;
	//ennemies
	vec2 speed = { 0, 0 };
	zone* expected_dest = nullptr;
	float turns2dest;
	//mine
};
struct player
{
	std::vector<drone> drones;
	std::vector<zone*> zones;
	vec2 zone_center;
	int score = 0;
	int id();
	player() :zones(){}
};

struct task
{
	int drone_id;
	vec2 pos;
	task(){}
	task(int drone_id, vec2 pos) :drone_id(drone_id), pos(pos){}
};
struct objective
{
	zone* zone = nullptr;
	int radius;
	int n_needed;
	std::vector<int> candidates;//drone id
	int value;
	std::vector<objective*> depends;
	bool done = false;
	int n_contractors = 0;
};

static const vec2 map_size = { 4000, 1800 };
int n_zones, n_drones, n_players, my_id;
std::vector<player> players;
std::vector<zone> zones;
int zone::id(){ return this - &zones[0]; }
int player::id(){ return this - &players[0]; }

int  vec2::turns2(vec2 target) const{ return int(std::ceil(norm(*this - target) / 100) + 0.1); } //game is doing secret conspiracy here... beware !
//int  vec2::turns2(zone target) const{return int(std::floor(norm(*this-target.pos)-1)+0.1)/100;} //game is doing secret conspiracy here... beware !
int  vec2::turns2(zone target) const{ return int(std::ceil((norm(*this - target.pos) - 100) / 100) + 0.1); } //game is doing secret conspiracy here... beware !
int drone::turns2(vec2 target) const{ return pos.turns2(target); }
int drone::turns2(zone target) const{ return pos.turns2(target); }//cache if needed

std::default_random_engine random_engine;
std::uniform_int_distribution<> coin(0, 1);
int flip_coin()
{
	return coin(random_engine);
}

void intersect(vec2 c1, float r1_turns,
	vec2 c2, float r2_turns, std::set<vec2>* inter)
{
	vec2 c2toc1 = c1 - c2;
	float r1 = (r1_turns)* 100 - 1, r2 = (r2_turns)* 100 - 1, dist = norm(c2toc1);
	if (dist == 0){ return; } 	//careful... 
	if (dist > r1 + r2){ return; }	//disks are disjoint
	if (dist + r2 < r1){ return; } //c2 is inside c1
	if (dist + r1 < r2){ return; } //c1 is inside c2
	float frac = ((r2*r2 - r1*r1) / dist / dist + 1) / 2;
	float h = std::sqrt(r2*r2 - frac*dist*frac*dist);
	vec2 m = c2 + c2toc1*frac;
	vec2 inter1 = m + h*vec2{ c2toc1.y, -c2toc1.x } / dist;
	vec2 inter2 = m + h*vec2{ -c2toc1.y, c2toc1.x } / dist;
	if (inter1.x > 0 && inter1.y>0 && inter1.x < map_size.x && inter1.y < map_size.y) inter->insert(inter1);
	if (inter2.x > 0 && inter2.y > 0 && inter2.x < map_size.x && inter2.y < map_size.y) inter->insert(inter2);
	//std::cerr<<c1<<","<<r1<<" inter "<<c2<<","<<r2<<" : "<<(m+h*vec2({c2toc1.y,-c2toc1.x})/dist)<<", "<<(m+h*vec2({-c2toc1.y,c2toc1.x})/dist)<<std::endl;
}

struct decision_context
{
	std::vector<task> task_per_drone;
	std::vector<std::set<vec2> > inter_set;
	std::vector<std::vector<objective*>> contracts;
	decision_context() :task_per_drone(n_drones), inter_set(n_drones), contracts(n_drones){}
	bool add_objective(objective& obj)
	{
		if (obj.done)
			return true;
		std::vector<task> tmp_tasks;
		std::vector<std::set<vec2>> tmp_inter_set(n_drones);
		std::vector<std::vector<objective*> > saved_contracts(n_drones);
		for (auto& di : obj.candidates){
			drone& d = players[my_id].drones[di];
			if (!contracts[di].empty()){
				//std::cerr<<"drone "<<di<<" contracted to zones: ";
				//for(auto c:contracts[di])std::cerr<<c->zone->id()<<"("<<c->radius<<") "; std::cerr<<std::endl;
				std::set<vec2> inter_others = inter_set[di];
				for (auto i = inter_others.begin();
					i != inter_others.end(); i++)
					if (i->turns2(*obj.zone) > obj.radius)
						inter_others.erase(i);
				if (inter_others.empty()){
					goto merge_failed;
				}//not compatible (else it is)
				{
					tmp_inter_set[di] = inter_others;
					std::set<vec2> inter_new;
					intersect(d.pos, 1, obj.zone->pos, obj.radius + 1, &inter_new);
					for (auto c : contracts[di])
						intersect(c->zone->pos, c->radius + 1, obj.zone->pos, obj.radius + 1, &inter_new);
					for (auto i = inter_new.begin(); i != inter_new.end(); i++)
						if (norm(*i - d.pos) > 100)
							inter_new.erase(i);
					for (auto c : contracts[di])
						for (auto i = inter_new.begin(); i != inter_new.end(); i++)
							if (i->turns2(*c->zone) > c->radius)
								inter_new.erase(i);
					tmp_inter_set[di].insert(inter_new.begin(), inter_new.end());

					vec2 m = { 0, 0 };
					for (auto& i : tmp_inter_set[di])
						m = m + i;
					m = m / tmp_inter_set[di].size();
					//check for rounding errors
					bool all_ok = true;
					if (d.turns2(m) > 1){
						std::cerr << "Merging contracts failed when adding ("
							<< obj.zone->id() << ", dist " << obj.radius << ") (point too far)\n";
						for (auto& i : tmp_inter_set[di])
							std::cerr << i << " : " << d.turns2(i) << std::endl;
						all_ok = false;
					}
					for (auto c : contracts[di])
						if (m.turns2(*c->zone) > c->radius){
							std::cerr << "Merging contracts failed when adding ("
								<< obj.zone->id() << ", dist " << obj.radius << ") (zone " << c->zone->id() << ", dist " << c->radius << ")\n";
							for (auto& i : tmp_inter_set[di])
								std::cerr << i << " : " << i.turns2(*c->zone) << std::endl;
							all_ok = false;
						}
					if (all_ok) {
						tmp_tasks.emplace_back(di, m);
						continue;
					}
				}
			merge_failed:
				if (tmp_tasks.size() >= obj.n_needed)
					continue;
				bool available = true;
				for (auto c : contracts[di])
					if (c->n_contractors == c->n_needed){
						available = false;
						break;
					}
				if (!available)
					continue;
				for (auto c : contracts[di])
					c->n_contractors--;
				saved_contracts[di] = contracts[di];
				contracts[di].clear();
				tmp_inter_set[di].clear();
			}
			if (contracts[di].empty()){
				intersect(d.pos, 1, obj.zone->pos, obj.radius + 1, &tmp_inter_set[di]);
				if (tmp_inter_set[di].empty())
					for (float i = 0; i < 6; i += 1)
						tmp_inter_set[di].insert(d.pos +
						vec2{ int(100 * std::cos(2 * M_PI*i / 6)), int(100 * std::sin(2 * M_PI*i / 6)) });
				tmp_tasks.emplace_back(di, obj.zone->pos);
			}
			//if(tmp_tasks.size()>=obj.n_needed)break;
		}
		if (tmp_tasks.size() >= obj.n_needed){
			for (auto& t : tmp_tasks){
				task_per_drone[t.drone_id] = t;
				inter_set[t.drone_id] = tmp_inter_set[t.drone_id];
				contracts[t.drone_id].push_back(&obj);
				std::cerr << "assigned drone " << t.drone_id
					<< " to (" << obj.zone->id() << ", dist " << obj.radius << ")" << std::endl;
			}
			obj.n_contractors = tmp_tasks.size();
			return true;
		}
		for (int di = 0; di < n_drones; di++)
			for (auto c : saved_contracts[di]){
				contracts[di].push_back(c);
				c->n_contractors++;
			}
		return false;
	}
};


int main()
{
	//init
	std::cin >> n_players >> my_id >> n_drones >> n_zones;
	random_engine.seed(my_id * 27);
	players.resize(n_players);
	for (auto& p : players)
		p.drones.resize(n_drones);
	zones.resize(n_zones);
	for (auto& z : zones)
		std::cin >> z.pos.x >> z.pos.y;

	std::vector<zone> sorted_zones = zones;
	std::sort(sorted_zones.begin(), sorted_zones.end(), [](zone a, zone b){return a.pos.x < b.pos.x; });
	int best = 0;
	//for(int i=0;i+2<n_zones;i++)if(sorted_zones[i+2].pos.x-sorted_zones[i].pos.x<sorted_zones[best+2].pos.x-sorted_zones[best].pos.x)best=i;
	//{int i=n_zones-3; if(sorted_zones[i+2].pos.x-sorted_zones[i].pos.x<sorted_zones[best+2].pos.x-sorted_zones[best].pos.x)best=i;}
	//{int i=n_zones-3; if(sorted_zones[i].pos.x-sorted_zones[i-1].pos.x>sorted_zones[best+3].pos.x-sorted_zones[best+2].pos.x)best=i;}
	vec2 lhome = (sorted_zones[0].pos
		+ sorted_zones[1].pos
		+ sorted_zones[2].pos) / 3;

	vec2 rhome = (sorted_zones[n_zones - 1].pos
		+ sorted_zones[n_zones - 2].pos
		+ sorted_zones[n_zones - 3].pos) / 3;

	vec2 lfront = (sorted_zones[3].pos + sorted_zones[4].pos) / 2;
	vec2 rfront = (sorted_zones[n_zones - 4].pos + sorted_zones[n_zones - 5].pos) / 2;
	vec2 best3_home = (norm(lhome - lfront) < norm(rhome - rfront)) ? rhome : lhome;
	//vec2* default_home=(n_players==2)?&players[!my_id].zone_center:new vec2(map_size/2);
	vec2* default_home = (n_players == 2) ? &players[!my_id].zone_center : (n_players == 3) ? new vec2(map_size / 2) : &best3_home;
	vec2* curr_home = default_home;
	//compact, far from the rest, far from enemies is better

	while (true){
		for (auto& p : players)
			p.zones.clear();
		for (auto& z : zones){
			std::cin >> z.owner_id;
			if (z.owner_id != -1){
				players[z.owner_id].zones.push_back(&z);
				players[z.owner_id].score++;
			}
		}
		for (auto& p : players){
			int i = 0;
			for (auto& d : p.drones){
				d.id = i++;
				d.player_id = p.id();
				vec2 prev_pos = d.pos;
				std::cin >> d.pos.x >> d.pos.y;
				if (p.id() == my_id)
					std::cerr << "drone " << d.id << ": " << d.pos << std::endl;
				if (prev_pos.x < 0)continue;
				d.speed = d.pos - prev_pos;
				d.expected_dest = nullptr;
				for (int i = 0; i < zones.size(); i++)
					if (norm(d.speed)>70
						&& abs(det(zones[i].pos - d.pos, d.speed / norm(d.speed))) < 100
						&& dot(zones[i].pos - d.pos, d.speed) > 0){
						int dist = d.turns2(zones[i]);
						if (d.expected_dest != nullptr && d.turns2dest < dist)
							continue;
						if (d.expected_dest != nullptr);//expected_dest changed !
						d.expected_dest = &zones[i];
						d.turns2dest = dist;
					}
			}
			if (p.zones.empty())
				p.zone_center = map_size / 2;
			else{
				p.zone_center = { 0, 0 };
				for (auto z : p.zones)
					p.zone_center = p.zone_center + z->pos;
				p.zone_center = p.zone_center / p.zones.size();
			}
		}
		curr_home = (players[my_id].zones.size() >= 3) ? &players[my_id].zone_center : default_home;

		//find objectives 
		std::list<objective> objectives;
		for (auto& z : zones){
			bool is_my_zone = (z.owner_id == my_id);
			//compute attackers for zone z
			for (auto& p : players)
				std::sort(p.drones.begin(), p.drones.end(), [z](drone a, drone b){return a.turns2(z) < b.turns2(z); });
			std::vector<std::vector<drone>> attackers(n_drones);
			for (int di = 0; di < n_drones; di++)
				attackers[di].push_back(players[(my_id + 1) % n_players].drones[di]);
			for (int pi = 2; pi < n_players; pi++)
				for (int di = 0; di < n_drones; di++){
					int diff = attackers[di][0].turns2(z) - players[(my_id + pi) % n_players].drones[di].turns2(z);
					if (diff > 0)
						attackers[di].clear();
					if (diff >= 0)
						attackers[di].push_back(players[(my_id + pi) % n_players].drones[di]);
				}
			std::cerr << (is_my_zone ? "+" : " ") << "Zone " << z.id();
			std::cerr << " allies  :";
			for (auto& d : players[my_id].drones)
				std::cerr << std::setw(3) << d.turns2(z);
			std::cerr << " enemies :";
			for (auto& a : attackers)
				std::cerr << std::setw(3) << a[0].turns2(z);
			std::cerr << " contested : ";

			std::vector<objective*> curr_depends;
			//compute objectives for zone z
			for (int di = 0; di < n_drones - 1; di++){
				bool contested = false;
				for (auto& d : attackers[di])
					if (d.expected_dest == &z || d.turns2(z) == 0){
						contested = true; break;
					}
				std::cerr << (contested ? "x " : "o ");
				if (is_my_zone){
					if (attackers[di][0].turns2(z) == attackers[di + 1][0].turns2(z))
						continue;
					int mydi = di;
					int diff = attackers[di][0].turns2(z) - players[my_id].drones[mydi].turns2(z);
					objective obj;
					obj.radius = std::max(attackers[di][0].turns2(z) - 1, 0);
					if (diff < 0){
						is_my_zone = false;
						continue;
					}//cannot defend
					else if (diff <= 1){
						while (mydi + 1 < n_drones && players[my_id].drones[mydi + 1].turns2(z) <= obj.radius + 1)
							mydi++;
						for (int i = 0; i <= mydi; i++)
							if (players[my_id].drones[i].turns2(z) >= obj.radius)
								obj.candidates.push_back(players[my_id].drones[i].id);
					}
					else if (diff > 1)
						continue;//no action needed

					obj.zone = &z;
					obj.value = 42 + 10 * (attackers[di + 1][0].turns2(z) - attackers[di][0].turns2(z)) / attackers[di + 1][0].turns2(z);

					obj.n_needed = di + 1 - (mydi + 1 - obj.candidates.size());
					obj.depends = curr_depends;
					objectives.push_back(obj);
					curr_depends.push_back(&objectives.back());
				}
				else for (int mydi = di; mydi <= di; mydi++){
					//for(int mydi=di;mydi<n_drones;mydi++){
					while (mydi + 1 < n_drones
						&& players[my_id].drones[mydi].turns2(z) == players[my_id].drones[mydi + 1].turns2(z))
						mydi++;
					int diff = attackers[di][0].turns2(z) - players[my_id].drones[mydi].turns2(z);
					objective obj;
					obj.radius = std::max(players[my_id].drones[mydi].turns2(z) - 1, 0);
					obj.zone = &z;
					if (diff >= 1){
						is_my_zone = true;
						for (int i = 0; i <= mydi; i++)
							if (players[my_id].drones[i].turns2(z) >= obj.radius)
								obj.candidates.push_back(players[my_id].drones[i].id);
						obj.value = 40 + 10 * (attackers[di + 1][0].turns2(z) - players[my_id].drones[mydi].turns2(z)) / attackers[di + 1][0].turns2(z);
					}
					else if (!contested){
						if (diff >= -1){
							for (int i = 0; i <= mydi; i++)
								if (players[my_id].drones[i].turns2(z) >= obj.radius)
									obj.candidates.push_back(players[my_id].drones[i].id);
							obj.value = 10 + 10 * (attackers[di + 1][0].turns2(z) - players[my_id].drones[mydi].turns2(z)) / attackers[di + 1][0].turns2(z);
						}
						else{
							continue;
							//for(int i=0;i<=mydi;i++)
							//if(players[my_id].drones[i].turns2(z)==obj.radius)
							//obj.candidates.push_back({players[my_id].drones[i].id,z.pos,action::stay});
							//else if(players[my_id].drones[i].turns2(z)==obj.radius+1)
							//obj.candidates.push_back({players[my_id].drones[i].id,z.pos,action::go});
							//obj.value=10+10*(attackers[di+1][0].turns2(z)-players[my_id].drones[mydi].turns2(z))/attackers[di+1][0].turns2(z);
						}
					}
					else continue;
					obj.n_needed = di + 1 - (mydi + 1 - obj.candidates.size());
					objectives.push_back(obj);
					if (is_my_zone){
						curr_depends.clear();
						curr_depends.push_back(&objectives.back());
					}
				}
			}
			std::cerr << z.pos << std::endl;
		}
		std::cerr << "Found " << objectives.size() << " objectives." << std::endl;

		//chose a set of objectives and assign tasks
		decision_context decisions;

		for (auto& p : players)
			std::sort(p.drones.begin(), p.drones.end(), [](drone a, drone b){return a.id < b.id; });
		//for(auto& obj:objectives)obj.value=obj.value/std::sqrt(obj.radius+1);
		objectives.sort([](objective a, objective b){return a.value == b.value ? flip_coin() : a.value > b.value; });

		for (auto& obj : objectives){
			obj.depends.push_back(&obj);
			bool dep_done = true;
			decision_context tmp_context = decisions;
			for (auto dep : obj.depends)
				if (!tmp_context.add_objective(*dep)){
					dep_done = false;
					break;
				}
			if (dep_done){
				for (auto dep : obj.depends)
					dep->done = true;
				decisions = tmp_context;
			}
			else{//this is not nice but...
				for (auto& o : objectives)
					o.n_contractors = 0;
				for (int di = 0; di < n_drones; di++)
					for (auto c : decisions.contracts[di]){
						c->n_contractors++;
					}
			}
		}
		for (int di = 0; di < n_drones; di++){
			bool available = true;
			for (auto c : decisions.contracts[di])
				if (c->n_contractors == c->n_needed){
					available = false;
					break;
				}
			if (!available)
				continue;
			for (auto c : decisions.contracts[di])
				c->n_contractors--;
			decisions.contracts[di].clear();
		}
		for (auto& obj : objectives){
			std::cerr << (obj.done ? "!" : " ") << "score: " << obj.value << ", " << obj.n_needed << " drone(s) needed to ";
			if (obj.zone)
				std::cerr << "zone " << obj.zone->id();
			else
				std::cerr << "home?";
			std::cerr << " at dist " << obj.radius << " from:";
			for (auto& di : obj.candidates){
				bool contracted = false;
				for (auto c : decisions.contracts[di])
					if (c == &obj){
						contracted = true;
						break;
					}
				std::cerr << " " << (contracted ? "!" : " ") << di;
			}
			std::cerr << std::endl;
		}
		for (int i = 0; i < n_drones; i++)
			if (decisions.contracts[i].empty()){
				decisions.task_per_drone[i] = { i, *curr_home };
			}

		//output results
		for (auto& t : decisions.task_per_drone)
			std::cout << t.pos << std::endl;
	}

	return 0;
}