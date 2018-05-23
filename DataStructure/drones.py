# coding: utf8
from __future__ import division

import sys
import math
import copy
import time

# init

W = 4000
H = 1800 

test = 0

if len(sys.argv) > 1 and sys.argv[1] == "_test_":
	test = 1

t = raw_input()
if t == "#test":
	test = 1
	t = raw_input()

P,I,D,Z = [int(i) for i in t.split()]

zones = [[int(a) for a in raw_input().split()] for _ in xrange(Z)]

scores = [0 for p in xrange(P)]

for i in xrange(Z):
	zones[i].append(-1)

BAR = []
drones = []
turn = 0
nb_zones_player = []
mode_defense = 0

# fonctions

def getMs():
	return int(round(time.time() * 1000))

def distance(a,b):
	"""Distance de 2 objets [x,y]"""
	return math.hypot(a[0]-b[0],a[1]-b[1])


def dist_drone_zone(dr,z):
	"""Distance d'un drone Ã  une zone en tours"""
	return max(0,int(math.ceil(distance(dr,z)/100))-1)


def zones_dist(a,b):
	if a == b: return 0
	else: return zones_dist_[a][b]


def barycentre(tab):
	"""[x,y] barycentre des positions dans tab"""
	if len(tab) == 0: return [0,0]
	x=0
	y=0
	for e in tab:
		x += e[0]
		y += e[1]
	
	return [int(x/len(tab)),int(y/len(tab))]


def all_dist_zone_zone(zones):
	global zones_dist_
	zones_dist_ = [[0 for a in xrange(Z)] for b in xrange(Z)]
	for a in xrange(Z-1):
		for b in xrange(a+1,Z):
			d = distance(zones[a],zones[b])
			zones_dist_[a][b] = d
			zones_dist_[b][a] = d


def all_dist_drone_zone(drones,zones):
	"""
	Met en 3Ã¨me ligne chaque drone le tableau de la distance
	avec chaque zone
	"""
	for p in xrange(P):
		for d in xrange(D):
			drone = drones[p][d]
			last_d = []
			if len(drone) < 3: drone.append(0)
			else: last_d = copy.deepcopy(drone[2])
			drone[2] = [dist_drone_zone(drones[p][d],zones[z]) for z in xrange(Z)]

			if p != I and len(last_d) > 0:
				# corrige l'estimation de position des adversaires
				for z in xrange(Z):
					delta = drone[2][z] - last_d[z]
					if abs(delta) > 1:
						drone[2][z] -= math.copysign(1,delta)
					elif delta == 0:
						pcmp =  a_step_round(last_d[z],zones[z])
						if pcmp[0] == drone[0] and pcmp[1] == drone[1]:
							drone[2][z] -= 1


def min_drone_to_control(zones,drones,i_zone,max_turn,max_drone_limit,ret) :
	"""
	Pour une zone, trouve les possibilitÃ©s de contrÃ´le
	au cours du temps
	retour : [[i_zone, winner (I ou -1), min_drone, turn, [drones],mode(0:defense,1:attaque), esperance]]
	"""
	zone = zones[i_zone]
	p_control = zone[2]

	tab_drones = [[] for _ in xrange(P)]
	last_max_drone_2 = 0

	for turn in xrange(max_turn):
		max_drone = 0
		max_drone_2 = 0
		tab_winners = []
		change = 0

		dist0 = turn+2

		for p in xrange(P):
			for d in xrange(D):
				drone = drones[p][d]
				dist = drone[2][i_zone]
				if dist < dist0 and (dist >= dist0-1 or turn==0): 
					tab_drones[p].append(d)
					change = 1

			nb_drone = len(tab_drones[p])

			if nb_drone > 0:
				if nb_drone > max_drone:
					max_drone_2 = max_drone
					max_drone = nb_drone
					tab_winners = [p]

				elif nb_drone == max_drone:
					max_drone_2 = max_drone
					tab_winners.append(p)

				elif nb_drone > max_drone_2 :
					max_drone_2 = nb_drone

		if max_drone_2 > last_max_drone_2: 
			change = 1

		p_control0 = p_control

		l = len(tab_winners)
		if l == 1 and p_control != tab_winners[0]: 
			p_control = tab_winners[0]
			change = 1
			max_drone_2 += 1

		if change and p_control0 == I and p_control != I and len(ret)>0 and ret[len(ret)-1][6] == -1:
			# esperance de vie de la conquete
			obj = ret[len(ret)-1]
			obj[6] = turn - obj[3]

		if change and ( p_control == I or 
				( p_control == -1 and l==2 and (I in tab_winners))) and max_drone_2 <= max_drone_limit:
			mode = 0
			if p_control != p_control0: mode = 1
			ret.append([i_zone, p_control, max_drone_2, turn,
				copy.deepcopy(tab_drones[I]), mode, -1])

		last_max_drone_2 = max_drone_2


def obj_i_can(zones,drones):
	if turn < 180:
		if P < 3: max_turn = 40
		else: max_turn = 25
	else: 
		max_turn = 40

	#if mode_defense: max_drone = D
	#else: max_drone = max(2,math.ceil(Z/D))
	max_drone = D
	ret = []
	for i in xrange(Z):
		min_drone_to_control(zones,drones,i,max_turn,max_drone,ret) 
	return ret


def sort_control_i_can(tab,mode_defense):
	"""Trie la liste prÃ©cÃ©dente"""
	
#	if turn < 180:
#		max_drone = max(2,math.ceil(Z/D))
#	else: 
	max_drone = D

	def compare(a,b): 

		if mode_defense:
			#privilÃ©gie la dÃ©fense
			ad = 0
			bd = 0
			if a[5] == 0 and zones[a[0]][2] == I: ad = 1
			if b[5] == 0 and zones[b[0]][2] == I: bd = 1
			if a and not b: return -1
			if b and not a: return 1
		else:
			# pas trop de drones
			if a[2] > max_drone and b[2] <= max_drone: return 1
			elif b[2] > max_drone and a[2] <= max_drone: return -1

		# proche + esperance
		if a[6] == -1: ae = 10
		else: ae = a[6]

		if b[6] == -1: be = 10
		else: be = b[6]

		a_ = - a[3] + ae
		b_ = - b[3] + be
		if a_ > b_: return -1
		elif b_ > a_: return 1

		# min drone
		elif a[2] < b[2]: return -1
		elif a[2] > b[2]: return 1
		# proche
		if a[3] < b[3]: return -1
		elif a[3] > b[3]: return 1
		# attaque d'abord
		elif a[5] > b[5]: return -1
		elif a[5] < b[5]: return 1

		else: return 0

	tab.sort(cmp=compare)

	# passe devant les attaques Ã  plus faible nombre
	if mode_defense: return
	l = len(tab)
	if l < 3: return
	for a in xrange(l-2):
		for b in xrange(a+1,l):
			if tab[b][5] == 1 and tab[a][2] > 2 and tab[b][2]*2 <= tab[a][2]:
				tab.insert(a, tab.pop(b))
	

def set_obj_to_drones(tab_i_can, drones_player):
	"""
	Trouve des objectifs et obj secondaire Ã  chaque drone
	Retour: [[[nb_turn,i_zone]]]
	"""

	rep = [[] for _ in xrange(D)]
	rep2 = [[] for _ in xrange(D)]

	drone_to_zone = [[] for _ in xrange(Z)]

	for o in tab_i_can:
		i_z = o[0]
		nb_min = o[2] - len(drone_to_zone[i_z])
		if nb_min <= 0: continue
		drones_ok = []
		drones_nok = []

		def drones_compare(a,b):
		# prend d'abord les drones dÃ©jÃ  occupÃ©s
		# puis les drones les plus loins
			la = len(rep[a])
			lb = len(rep[b])
			if la > lb: return -1
			elif la < lb: return 1
			da = distance(drones_player[a],zones[i_z])
			db = distance(drones_player[b],zones[i_z])
			if 1:
				#plus logique
				if da < db: return -1
				elif da > db: return 1
			else:
				#utilise les plus loins
				if da <=100 and db <= 100:
					if da < db: return -1
					elif da > db: return 1
				else:
					if da > db: return -1
					elif da < db: return 1
	
			return 0

		for d in o[4]:
			l = len(rep[d])
			if l == 0 or ( 
					( d not in drone_to_zone[i_z] ) and zones_dist(rep[d][l-1][1], i_z) - 150 <= 100 * abs(o[3] - rep[d][l-1][0])):
				drones_ok.append(d)
			elif d not in drone_to_zone[i_z]:
				drones_nok.append(d)

		if len(drones_ok) >= nb_min:
			drones_ok.sort(cmp=drones_compare)
			for i in xrange(nb_min):
				d = drones_ok[i]
				drone_to_zone[i_z].append(d)
				# si dÃ©fense et 2eme plus loin, oublie pour le drone
#				if o[5] == 1 or len(rep[d]) == 0: 
				rep[d].append([o[3],i_z])
		else:
			for d in drones_ok: drones_nok.append(d)
			for d in drones_nok:
				rep2[d].append([o[3],i_z])

	for d in xrange(D): 
		rep[d] += rep2[d]

	return rep


def complete_obj_to_drones(drones_player, obj, best_t):
	"""Trouve un autre objectif aux drones qui ont du temps"""
	for d in xrange(D):
		obj_drone = obj[d]
		drone = drones_player[d]
		for z in best_t[d]:
			if drone[2][z] < 2: continue # pas si le drone est super proche
			ok = 1
			for o in obj_drone: 
				if o[1] == z: 
					ok = 0
					break
			if ok:
				obj_drone.append([drone[2][z]-1, z])
				break


def pos_round(pos,ref=[]):
	ret = []
	for i in xrange(2):
		p = pos[i]
		if len(ref) == 0: p = math.floor(p+0.5)
		else:
			if ref[i] > pos[i]:
				p = math.ceil(p)
			else: 
				p = math.floor(p)
	
		ret.append(int(p))
	return ret
		


def a_step_real(src,dest,step=100):
	d = distance(src,dest)
	if d <= step: return [dest[0],dest[1]]

	pos = []
	for i in xrange(2):
		a = src[i]
		b = dest[i]
		p = a + (b-a)/d*step
		pos.append(p)
	
	return pos


def a_step_round_back(src,dest,step=100):
	"""
	Evite de dÃ©passer la distance 100 mÃªme avec
	les arrondis des coords en integer
	"""
	return pos_round(a_step_real(src,dest,step),src)


def a_step_round(src,dest,step=100):
	"""Un pas avec l'arrondi du serveur"""
	return pos_round(a_step_real(src,dest,step))	
	

def n_step_round_back(src,dest,nb):
	"""Remplace a_step(,,n*100)"""
	return pos_round(a_step_real(src,dest,nb*100),src)


def best_point_for_two_dir(drone,z1,z2,turn1,zones):
	"""
	Trouve le meilleur point oÃ¹ aller
	Pour un objectif avec un nombre de tours prÃ©cis,
	en prenant en compte un 2Ã¨me objectif
	"""
	dist_max = (turn1+1) * 100;
	zone1 = zones[z1]
	zone2 = zones[z2]

#	print >> sys.stderr, "debug: best two dirs zones ", z1, " et ", z2, " en ", turn1, " tour for ", drone[0], "x", drone[1], " dist max:", dist_max

	if drone[0] == zone1[0] and drone[1] == zone1[1]:
		return [zone2[0], zone2[1]]

	if drone[2][z1] > turn1+2:
		print >> sys.stderr, "warn: drone trop Ã©loignÃ© de " + str(z1)
		return [zone1[0], zone1[1]] 

	#compare 4 possibilitÃ©s : aller vers la zone 2, le point idÃ©al,
	#et les intersections des cercles

	poss = [a_step_round_back(drone,zone2)]

	# trouve le pt idÃ©al
	#if zones_dist(z1,z2) <= dist_max: 
	#	ideal = [zone2[0],zone2[1]]
	#else: 
	ideal = a_step_real(zone1,zone2, dist_max) 

	#if distance(drone,ideal) <= 100: 
	#	poss.append(ideal)
	#else:
	pos = a_step_round_back(drone,ideal)
	if dist_drone_zone(pos,zone1) > turn:
		ideal = a_step_real(ideal,zone1,3)
		pos = a_step_round_back(drone,ideal)
	poss.append(pos)

	if drone[2][z1]+1 > turn1:
		inter = [p for p in circle_intersection(drone,100,zone1,dist_max)]
		for p0 in inter:
			p = a_step_round_back(drone,p0)
			if dist_drone_zone(p,zone1) > turn1:
				# essaie de rapprocher le point de zone1
				ok = 0
				for i in xrange(10):
					p = a_step_round_back(drone,a_step_real(p0,zone1,i))
					if dist_drone_zone(p,zone1) <= turn1:
						ok = 1
						break
			#	if not ok : 
			#		print >> sys.stderr, "warn: intersection tjs trop loin de z1",drone[0],drone[1],zone1[0],zone1[1],p0,p,dist_max,turn1
			poss.append(p)

	best = -1
	d_best = -1
	for i in xrange(len(poss)):
		pos = poss[i]
		d = dist_drone_zone(pos,zone2)
		if dist_drone_zone(pos,zone1) <= turn1 and (
				best == -1 or d < d_best ):
			best = i
			d_best = d

	if best == -1:
	#	print >> sys.stderr, "warn: echec de best_point_for_two_dir"
		return [zone1[0],zone1[1]]
	else:
		return poss[best]


def circle_intersection(c1,r1,c2,r2):
	x1 = c1[0]
	y1 = c1[1]
	x2 = c2[0]
	y2 = c2[1]

	#http://stackoverflow.com/questions/3349125/circle-circle-intersection-points
	d = distance(c1,c2)
	if d == 0: return []

	a = (r1*r1 - r2*r2 + d*d)/(2*d)
	b = r1*r1 - a*a
	if b < 0: return []
	
	h = math.sqrt(b)

	x3 = (x2 - x1)*(a/d) + x1
	y3 = (y2 - y1)*(a/d) + y1

	x4 = h * (y2-y1)/d
	y4 = h * (x2-x1)/d

	pos1 = [x3+x4,y3-y4]
	pos2 = [x3-x4,y3+y4]

	return [pos1,pos2]


def drones_where_to_going(zones,drones_player,drones_obj):
	"""Retourne un tableau de coords avec un objectif pour chaque drone"""
	ret = []

	for d in xrange(D):
		tab_obj = drones_obj[d]
		l = len(tab_obj)

		if l == 0:
			pos = copy.deepcopy(BAR)
		else:
			o = tab_obj[0]
			zone = zones[o[1]]
			if l == 1:
				pos = [zone[0],zone[1]]
			else:
				drone = drones_player[d]
				nb_confort = 0
				ok = 1
				while ok and nb_confort < l:
					#dist_min = max(0,tab_obj[nb_confort][0]-1)
					dist_min = tab_obj[nb_confort][0]
					if drone[2][tab_obj[nb_confort][1]] < dist_min:
						nb_confort += 1
					else: ok = 0

				if nb_confort == l:
					zobj = zones[tab_obj[l-1][1]]
					pos = [zobj[0],zobj[1]]

				elif nb_confort == 0:
					#cherche la meilleure 2eme zone
					z2 = -1
					for i in xrange(1,l):
						dist_min = tab_obj[i][0]
						if drone[2][tab_obj[i][1]] >= dist_min:
							z2 = i
							break
					if z2 == -1: z2 = l-1
					#print >> sys.stderr, "2eme zone:" + str(tab_obj[z2][1])
					#dist_min = max(0,o[0]-1)
					dist_min = o[0]
					o2 = tab_obj[z2]
					pos = best_point_for_two_dir(drone,o[1],o2[1],dist_min,zones)


				elif nb_confort == 1:
					#entre les zones 0 et 1
					#dist_min = max(0,o[0]-1)
					dist_min = o[0]
					o2 = tab_obj[1]
					pos = best_point_for_two_dir(drone,o[1],o2[1],dist_min,zones)

				else:
					# au moins deux zones sont confortables,
					# essaye d'atteindre la suivante
					zobj = zones[tab_obj[nb_confort][1]]
					pos = [zobj[0],zobj[1]]
					
		ret.append(pos)
	
	return ret


def zone_nearest(drone):
	"""Trouve la zone la plus proche du drone"""
	d_min = 0
	i_zone = -1

	for z in xrange(Z):
		if i_zone == -1 or d_min > drone[2][z]:
			d_min = drone[2][z]
			i_zone = z

	return i_zone 


def set_obj_nearest_to_drones(drones_player):
	ret = []
	for d in xrange(D):
		ret.append([[0,zone_nearest(drones_player[d])]])
	
	return ret


def voronai_zones_drones(zones,drones):
	"""trouve le nombre de drone par joueur pour chaque zone"""
	ret = [[0 for _ in xrange(P)] for i in xrange(Z)]

	for p in xrange(P):
		for d in xrange(D):
			d_min = -1
			z_min = 0
			drone = drones[p][d]
			tab = drone[2]
			for z in xrange(Z):
				if z == 0 or d_min > tab[z]:
					d_min = tab[z]
					z_min = z

			ret[z_min][p] += 1
	return ret 


def best_target_drones(voronai,zones,drones_player):
	""" trouve let meilleures cibles pour chaque drone"""
	max_ennemy = []
	for z in xrange(Z):
		me = 0
		for p in xrange(P):
			if p != I:
				me = max(me,voronai[z][p])
		max_ennemy.append(me)

	def zone_cmp(a,b):
		if max_ennemy[a[0]] < max_ennemy[b[0]]: return -1
		elif max_ennemy[a[0]] > max_ennemy[b[0]]: return 1
		elif a[1] < b[1]: return -1
		elif a[1] > b[1]: return 1
		else: return 0
		
	ret = []
	for d in xrange(D):
		tab = []
		for z in xrange(Z):
			if zones[z][2] != I:
				tab.append([z,drones_player[d][2][z]])
		tab.sort(cmp=zone_cmp)
	
		ret.append([t[0] for t in tab])

	return ret


def maj_scores(scores,zones):
	"""Les 2Â fonctions suivantes ne sont pas encore utilisÃ©es"""
	global nb_zones_player
	nb_zones_player = [0 for p in xrange(P)]

	for z in xrange(Z):
		p = zones[z][2]
		if p != -1: 
			nb_zones_player[p] += 1 
			scores[p] += 1


def projection_scores(scores):
	tab = []
	nb_turn = 200 - turn
	for p in xrange(P):
		tab.append(scores[p] + nb_turn*nb_zones_player[p])
	return tab


def projection2rank(proj):
	me = proj[I]
	rank = 1
	for p in xrange(P):
		if p != I and ( proj[p] > me or (proj[p] == me and p > I )) :
			rank += 1
	return rank


def get_mode_defense(rank,zones):
	if rank != 1: return 0
	for z in zones:
		if z[2] == -1: return 0
	return 1


def svg(mvt):
	colors = ["red","blue","green","yellow"]
	color_neutral = "#666666"

	t = '<?xml version="1.0" encoding="utf-8"?>\n'
	a = [0,0]
	b = [0,0]
	for z in xrange(Z):
		for i in xrange(2):
			ref = zones[z][i]
			if z == 0 or a[i] > ref: a[i] = ref
			if z == 0 or b[i] < ref: b[i] = ref
	for p in xrange(P):
		for d in xrange(D):
			for i in xrange(2):
				ref = drones[p][d][i]
				if a[i] > ref: a[i] = ref
				if b[i] < ref: b[i] = ref
	
	b[0] += 100
	b[1] += 100

	ax = a[0] - 100
	ay = a[1] - 100
	w = str(b[0]-ax)
	h = str(b[1]-ay)

	t += '<svg width="' + w + '" height="' +  h + '">\n'
	t += '<rect x="0" y="0" width="' + w + '" height="' + h + '" style="fill:#FFFFFF" />'

	for z in xrange(Z):
		color = ""
		if zones[z][2] == -1: color = color_neutral
		else: color = colors[zones[z][2]]

		t += '<circle cx="' + str(zones[z][0]-ax) + '" cy="' + str(zones[z][1]-ay) + '" r="100" stroke="none" fill="' + color + '" fill-opacity="0.1" />\n'

	for p in xrange(P):
		color = colors[p]
		for d in xrange(D):
			t += '<circle cx="' + str(drones[p][d][0]-ax) + '" cy="' + str(drones[p][d][1]-ay) + '" r="3" stroke="none" fill="' + color + '" fill-opacity="0.8" />\n'
			t += '<circle cx="' + str(drones[p][d][0]-ax) + '" cy="' + str(drones[p][d][1]-ay) + '" r="100" stroke="' + color + '" fill="none" stroke-opacity="0.2" stroke-width="3" />\n'
			if p == I:
				t += '<line x1="' + str(drones[p][d][0]-ax) + '" y1="' + str(drones[p][d][1]-ay) + '" x2="' + str(mvt[d][0] - ax) + '" y2="' + str(mvt[d][1]-ay) + '" stroke="' + color + '" stroke-width="1" stroke-opacity="0.2" />\n'
	
	t += '</svg>'

	f = open("schema.svg","w")
	print >> f, t
	f.close()



# boucle main
BAR = barycentre(zones)
print >> sys.stderr, "Zones: ", zones
all_dist_zone_zone(zones)
if test: turn = 1

next_pos = []

while 1 :
	for i in xrange(Z):
		zones[i][2] = int(raw_input())

	tms0 = getMs()

	if turn > 0:
		drones_old = drones

	drones = [[[int(a) for a in raw_input().split()] for d in xrange(D)] for p in xrange(P)]
	# mes positions en rÃ©el
	for d in xrange(len(next_pos)): 
		for i in xrange(2):
			drones[I][d][i] = next_pos[d][i]

	all_dist_drone_zone(drones,zones)
	maj_scores(scores,zones)
	projection = projection_scores(scores)
	rank = projection2rank(projection)
	mode_defense = get_mode_defense(rank,zones)

	print >> sys.stderr, "Tour ", turn
	print >> sys.stderr, "Scores: ", scores
	print >> sys.stderr, "Projection: ", projection, "rank: ", rank
	if mode_defense: print >> sys.stderr, "MODE DEFENSE"


	if turn == 0:
		obj1 = set_obj_nearest_to_drones(drones[I])

	else:
		i_can = obj_i_can(zones,drones)
		sort_control_i_can(i_can,mode_defense)

		print >> sys.stderr, "i_zone, winner, min_drone, turn, [drones],mode"
		print >> sys.stderr, "objectifs: ",i_can

		voronai = voronai_zones_drones(zones,drones)
		best_targets = best_target_drones(voronai,zones,drones[I])
		print >> sys.stderr, "objectifs de secours: ",best_targets

		obj1 = set_obj_to_drones(i_can, drones[I])
		complete_obj_to_drones(drones[I],obj1,best_targets)

		print >> sys.stderr
		for d in xrange(D):
			print  >> sys.stderr, "drone " + str(d) + " " + str(drones[I][d][0]) + "x" + str(drones[I][d][1]) + " : distances zones " ,
			print >> sys.stderr, drones[I][d][2]
			print >> sys.stderr, "obj (turn,zone): ",obj1[d],"\n"

	tab_pos = drones_where_to_going(zones,drones[I],obj1)

	for pos in tab_pos:
		print str(pos[0]) + " " + str(pos[1])

	# pos de mes drones pour le prochain tour
	next_pos = []
	for d in xrange(D):
		drone = drones[I][d]
		next_pos.append(a_step_real(drone,tab_pos[d]))

	print >> sys.stderr, "Mes drones: ", next_pos 

	print >> sys.stderr, str(getMs() - tms0) + "ms"

	if test: 
		svg(tab_pos)
		break

	turn += 1
