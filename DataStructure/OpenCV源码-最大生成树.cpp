void findMaxSpanningTree(int num_images,
	const std::vector<MatchesInfo> &pairwise_matches,
	Graph &span_tree, std::vector<int> &centers)
{
	Graph graph(num_images);
	std::vector<GraphEdge> edges;

	// Construct images graph and remember its edges
	for (int i = 0; i < num_images; ++i)
	{
		for (int j = 0; j < num_images; ++j)
		{
			if (pairwise_matches[i * num_images + j].H.empty())
				continue;
			float conf = static_cast<float>(pairwise_matches[i * num_images + j].num_inliers);
			graph.addEdge(i, j, conf);
			edges.push_back(GraphEdge(i, j, conf));
		}
	}

	DisjointSets comps(num_images);
	span_tree.create(num_images);
	std::vector<int> span_tree_powers(num_images, 0);

	// Find maximum spanning tree
	sort(edges.begin(), edges.end(), std::greater<GraphEdge>());
	for (size_t i = 0; i < edges.size(); ++i)
	{
		int comp1 = comps.findSetByElem(edges[i].from);
		int comp2 = comps.findSetByElem(edges[i].to);
		if (comp1 != comp2)
		{
			comps.mergeSets(comp1, comp2);
			span_tree.addEdge(edges[i].from, edges[i].to, edges[i].weight);
			span_tree.addEdge(edges[i].to, edges[i].from, edges[i].weight);
			span_tree_powers[edges[i].from]++;
			span_tree_powers[edges[i].to]++;
		}
	}

	// Find spanning tree leafs
	std::vector<int> span_tree_leafs;
	for (int i = 0; i < num_images; ++i)
		if (span_tree_powers[i] == 1)
			span_tree_leafs.push_back(i);

	// Find maximum distance from each spanning tree vertex
	std::vector<int> max_dists(num_images, 0);
	std::vector<int> cur_dists;
	for (size_t i = 0; i < span_tree_leafs.size(); ++i)
	{
		cur_dists.assign(num_images, 0);
		span_tree.walkBreadthFirst(span_tree_leafs[i], IncDistance(cur_dists));
		for (int j = 0; j < num_images; ++j)
			max_dists[j] = std::max(max_dists[j], cur_dists[j]);
	}

	// Find min-max distance
	int min_max_dist = max_dists[0];
	for (int i = 1; i < num_images; ++i)
		if (min_max_dist > max_dists[i])
			min_max_dist = max_dists[i];

	// Find spanning tree centers
	centers.clear();
	for (int i = 0; i < num_images; ++i)
		if (max_dists[i] == min_max_dist)
			centers.push_back(i);
	CV_Assert(centers.size() > 0 && centers.size() <= 2);
}