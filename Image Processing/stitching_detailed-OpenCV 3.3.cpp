#include <iostream>
#include <fstream>
#include <string>
#include "opencv2/opencv_modules.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching/detail/autocalib.hpp"
#include "opencv2/stitching/detail/blenders.hpp"
#include "opencv2/stitching/detail/timelapsers.hpp"
#include "opencv2/stitching/detail/camera.hpp"
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/stitching/detail/motion_estimators.hpp"
#include "opencv2/stitching/detail/seam_finders.hpp"
#include "opencv2/stitching/detail/warpers.hpp"
#include "opencv2/stitching/warpers.hpp"

#define ENABLE_LOG 1
#define LOG(msg) std::cout << msg
#define LOGLN(msg) std::cout << msg << std::endl

using namespace std;
using namespace cv;
using namespace cv::detail;

static void printUsage()
{
	cout <<
		"Rotation model images stitcher.\n\n"
		"stitching_detailed img1 img2 [...imgN] [flags]\n\n"
		"Flags:\n"
		"  --preview\n"
		"      Run stitching in the preview mode. Works faster than usual mode,\n"
		"      but output image will have lower resolution.\n"
		"  --try_cuda (yes|no)\n"
		"      Try to use CUDA. The default value is 'no'. All default values\n"
		"      are for CPU mode.\n"
		"\nMotion Estimation Flags:\n"
		"  --work_megapix <float>\n"
		"      Resolution for image registration step. The default is 0.6 Mpx.\n"
		"  --features (surf|orb)\n"
		"      Type of features used for images matching. The default is surf.\n"
		"  --matcher (homography|affine)\n"
		"      Matcher used for pairwise image matching.\n"
		"  --estimator (homography|affine)\n"
		"      Type of estimator used for transformation estimation.\n"
		"  --match_conf <float>\n"
		"      Confidence for feature matching step. The default is 0.65 for surf and 0.3 for orb.\n"
		"  --conf_thresh <float>\n"
		"      Threshold for two images are from the same panorama confidence.\n"
		"      The default is 1.0.\n"
		"  --ba (no|reproj|ray|affine)\n"
		"      Bundle adjustment cost function. The default is ray.\n"
		"  --ba_refine_mask (mask)\n"
		"      Set refinement mask for bundle adjustment. It looks like 'x_xxx',\n"
		"      where 'x' means refine respective parameter and '_' means don't\n"
		"      refine one, and has the following format:\n"
		"      <fx><skew><ppx><aspect><ppy>. The default mask is 'xxxxx'. If bundle\n"
		"      adjustment doesn't support estimation of selected parameter then\n"
		"      the respective flag is ignored.\n"
		"  --wave_correct (no|horiz|vert)\n"
		"      Perform wave effect correction. The default is 'horiz'.\n"
		"  --save_graph <file_name>\n"
		"      Save matches graph represented in DOT language to <file_name> file.\n"
		"      Labels description: Nm is number of matches, Ni is number of inliers,\n"
		"      C is confidence.\n"
		"\nCompositing Flags:\n"
		"  --warp (affine|plane|cylindrical|spherical|fisheye|stereographic|compressedPlaneA2B1|compressedPlaneA1.5B1|compressedPlanePortraitA2B1|compressedPlanePortraitA1.5B1|paniniA2B1|paniniA1.5B1|paniniPortraitA2B1|paniniPortraitA1.5B1|mercator|transverseMercator)\n"
		"      Warp surface type. The default is 'spherical'.\n"
		"  --seam_megapix <float>\n"
		"      Resolution for seam estimation step. The default is 0.1 Mpx.\n"
		"  --seam (no|voronoi|gc_color|gc_colorgrad)\n"
		"      Seam estimation method. The default is 'gc_color'.\n"
		"  --compose_megapix <float>\n"
		"      Resolution for compositing step. Use -1 for original resolution.\n"
		"      The default is -1.\n"
		"  --expos_comp (no|gain|gain_blocks)\n"
		"      Exposure compensation method. The default is 'gain_blocks'.\n"
		"  --blend (no|feather|multiband)\n"
		"      Blending method. The default is 'multiband'.\n"
		"  --blend_strength <float>\n"
		"      Blending strength from [0,100] range. The default is 5.\n"
		"  --output <result_img>\n"
		"      The default is 'result.jpg'.\n"
		"  --timelapse (as_is|crop) \n"
		"      Output warped images separately as frames of a time lapse movie, with 'fixed_' prepended to input file names.\n"
		"  --rangewidth <int>\n"
		"      uses range_width to limit number of images to match with.\n";
}


// Default command line args
vector<String> img_names;
bool preview = false;
bool try_cuda = false;
double work_megapix = 0.6;  //设置图片大小
double seam_megapix = 0.1;
double compose_megapix = -1;
float conf_thresh = 1.f;
string features_type = "surf";
string matcher_type = "homography";
string estimator_type = "homography";
string ba_cost_func = "ray";
string ba_refine_mask = "xxxxx";
bool do_wave_correct = true;
WaveCorrectKind wave_correct = detail::WAVE_CORRECT_HORIZ;
bool save_graph = false;
std::string save_graph_to;
string warp_type = "spherical";
int expos_comp_type = ExposureCompensator::GAIN_BLOCKS;
float match_conf = 0.3f;
string seam_find_type = "gc_color";
int blend_type = Blender::MULTI_BAND;
int timelapse_type = Timelapser::AS_IS;
float blend_strength = 5;
string result_name = "result.jpg";
bool timelapse = false;
int range_width = -1;


static int parseCmdArgs(int argc, char** argv)
{
	if (argc == 1)
	{
		printUsage();
		return -1;
	}
	for (int i = 1; i < argc; ++i)
	{
		if (string(argv[i]) == "--help" || string(argv[i]) == "/?")
		{
			printUsage();
			return -1;
		}
		else if (string(argv[i]) == "--preview")
		{
			preview = true;
		}
		else if (string(argv[i]) == "--try_cuda")
		{
			if (string(argv[i + 1]) == "no")
				try_cuda = false;
			else if (string(argv[i + 1]) == "yes")
				try_cuda = true;
			else
			{
				cout << "Bad --try_cuda flag value\n";
				return -1;
			}
			i++;
		}
		else if (string(argv[i]) == "--work_megapix")
		{
			work_megapix = atof(argv[i + 1]);
			i++;
		}
		else if (string(argv[i]) == "--seam_megapix")
		{
			seam_megapix = atof(argv[i + 1]);
			i++;
		}
		else if (string(argv[i]) == "--compose_megapix")
		{
			compose_megapix = atof(argv[i + 1]);
			i++;
		}
		else if (string(argv[i]) == "--result")
		{
			result_name = argv[i + 1];
			i++;
		}
		else if (string(argv[i]) == "--features")
		{
			features_type = argv[i + 1];
			if (features_type == "orb")
				match_conf = 0.3f;
			i++;
		}
		else if (string(argv[i]) == "--matcher")
		{
			if (string(argv[i + 1]) == "homography" || string(argv[i + 1]) == "affine")
				matcher_type = argv[i + 1];
			else
			{
				cout << "Bad --matcher flag value\n";
				return -1;
			}
			i++;
		}
		else if (string(argv[i]) == "--estimator")
		{
			if (string(argv[i + 1]) == "homography" || string(argv[i + 1]) == "affine")
				estimator_type = argv[i + 1];
			else
			{
				cout << "Bad --estimator flag value\n";
				return -1;
			}
			i++;
		}
		else if (string(argv[i]) == "--match_conf")
		{
			match_conf = static_cast<float>(atof(argv[i + 1]));
			i++;
		}
		else if (string(argv[i]) == "--conf_thresh")
		{
			conf_thresh = static_cast<float>(atof(argv[i + 1]));
			i++;
		}
		else if (string(argv[i]) == "--ba")
		{
			ba_cost_func = argv[i + 1];
			i++;
		}
		else if (string(argv[i]) == "--ba_refine_mask")
		{
			ba_refine_mask = argv[i + 1];
			if (ba_refine_mask.size() != 5)
			{
				cout << "Incorrect refinement mask length.\n";
				return -1;
			}
			i++;
		}
		else if (string(argv[i]) == "--wave_correct")
		{
			if (string(argv[i + 1]) == "no")
				do_wave_correct = false;
			else if (string(argv[i + 1]) == "horiz")
			{
				do_wave_correct = true;
				wave_correct = detail::WAVE_CORRECT_HORIZ;
			}
			else if (string(argv[i + 1]) == "vert")
			{
				do_wave_correct = true;
				wave_correct = detail::WAVE_CORRECT_VERT;
			}
			else
			{
				cout << "Bad --wave_correct flag value\n";
				return -1;
			}
			i++;
		}
		else if (string(argv[i]) == "--save_graph")
		{
			save_graph = true;
			save_graph_to = argv[i + 1];
			i++;
		}
		else if (string(argv[i]) == "--warp")
		{
			warp_type = string(argv[i + 1]);
			i++;
		}
		else if (string(argv[i]) == "--expos_comp")
		{
			if (string(argv[i + 1]) == "no")
				expos_comp_type = ExposureCompensator::NO;
			else if (string(argv[i + 1]) == "gain")
				expos_comp_type = ExposureCompensator::GAIN;
			else if (string(argv[i + 1]) == "gain_blocks")
				expos_comp_type = ExposureCompensator::GAIN_BLOCKS;
			else
			{
				cout << "Bad exposure compensation method\n";
				return -1;
			}
			i++;
		}
		else if (string(argv[i]) == "--seam")
		{
			if (string(argv[i + 1]) == "no" ||
				string(argv[i + 1]) == "voronoi" ||
				string(argv[i + 1]) == "gc_color" ||
				string(argv[i + 1]) == "gc_colorgrad" ||
				string(argv[i + 1]) == "dp_color" ||
				string(argv[i + 1]) == "dp_colorgrad")
				seam_find_type = argv[i + 1];
			else
			{
				cout << "Bad seam finding method\n";
				return -1;
			}
			i++;
		}

		else if (string(argv[i]) == "--blend")
		{
			if (string(argv[i + 1]) == "no")
				blend_type = Blender::NO;
			else if (string(argv[i + 1]) == "feather")
				blend_type = Blender::FEATHER;
			else if (string(argv[i + 1]) == "multiband")
				blend_type = Blender::MULTI_BAND;
			else
			{
				cout << "Bad blending method\n";
				return -1;
			}
			i++;
		}
		else if (string(argv[i]) == "--timelapse")
		{
			timelapse = true;

			if (string(argv[i + 1]) == "as_is")
				timelapse_type = Timelapser::AS_IS;
			else if (string(argv[i + 1]) == "crop")
				timelapse_type = Timelapser::CROP;
			else
			{
				cout << "Bad timelapse method\n";
				return -1;
			}
			i++;
		}
		else if (string(argv[i]) == "--rangewidth")
		{
			range_width = atoi(argv[i + 1]);
			i++;
		}
		else if (string(argv[i]) == "--blend_strength")
		{
			blend_strength = static_cast<float>(atof(argv[i + 1]));
			i++;
		}
		else if (string(argv[i]) == "--output")
		{
			result_name = argv[i + 1];
			i++;
		}
		else
			img_names.push_back(argv[i]);
	}
	if (preview)
	{
		compose_megapix = 0.6;
	}

	return 0;

}


int main(int argc, char* argv[])
{
#if ENABLE_LOG
	int64 app_start_time = getTickCount();
#endif

#if 0
	cv::setBreakOnError(true);
#endif

	int retval = parseCmdArgs(argc, argv);
	if (retval)
		return retval;

	// Check if have enough images
	int num_images = static_cast<int>(img_names.size());
	if (num_images < 2)
	{
		LOGLN("Need more images");
		return -1;
	}

	double work_scale = 1, seam_scale = 1, compose_scale = 1;
	bool is_work_scale_set = false, is_seam_scale_set = false, is_compose_scale_set = false;

	LOGLN("Finding features...");
#if ENABLE_LOG
	int64 t = getTickCount();
#endif

	Ptr<FeaturesFinder> finder;
	if (features_type == "surf")
	{
#ifdef HAVE_OPENCV_XFEATURES2D
		if (try_cuda && cuda::getCudaEnabledDeviceCount() > 0)
			finder = makePtr<SurfFeaturesFinderGpu>();
		else
#endif
			finder = makePtr<SurfFeaturesFinder>();

	}
	else if (features_type == "orb")
	{
		finder = makePtr<OrbFeaturesFinder>();
	}
	else
	{
		cout << "Unknown 2D features type: '" << features_type << "'.\n";
		return -1;
	}

	Mat full_img, img;
	vector<ImageFeatures> features(num_images);
	/*
	struct CV_EXPORTS ImageFeatures
	{
	int img_idx;
	Size img_size;
	std::vector<KeyPoint> keypoints;
	UMat descriptors;
	};

	KeyPoint {
	CV_PROP_RW Point2f pt; //!< coordinates of the keypoints
	CV_PROP_RW float size; //!< diameter of the meaningful keypoint neighborhood
	CV_PROP_RW float angle; //!< computed orientation of the keypoint (-1 if not applicable);
	//!< it's in [0,360) degrees and measured relative to
	//!< image coordinate system, ie in clockwise.
	CV_PROP_RW float response; //!< the response by which the most strong keypoints have been selected. Can be used for the further sorting or subsampling
	CV_PROP_RW int octave; //!< octave (pyramid layer) from which the keypoint has been extracted
	CV_PROP_RW int class_id; //!< object class (if the keypoints need to be clustered by an object they belong to)
	}
	*/
	vector<Mat> images(num_images);
	vector<Size> full_img_sizes(num_images);
	double seam_work_aspect = 1;

	for (int i = 0; i < num_images; ++i)
	{
		full_img = imread(img_names[i]);
		full_img_sizes[i] = full_img.size();

		if (full_img.empty())
		{
			LOGLN("Can't open image " << img_names[i]);
			return -1;
		}

		if (work_megapix < 0)
		{
			img = full_img;
			work_scale = 1;
			is_work_scale_set = true;
		}
		else
		{
			if (!is_work_scale_set)
			{
				work_scale = min(1.0, sqrt(work_megapix * 1e6 / full_img.size().area()));
				is_work_scale_set = true;
			}
			resize(full_img, img, Size(), work_scale, work_scale);
		}
		if (!is_seam_scale_set)
		{
			seam_scale = min(1.0, sqrt(seam_megapix * 1e6 / full_img.size().area()));
			seam_work_aspect = seam_scale / work_scale;
			is_seam_scale_set = true;
		}

		(*finder)(img, features[i]);
		features[i].img_idx = i;
		LOGLN("Features in image #" << i + 1 << ": " << features[i].keypoints.size());

		resize(full_img, img, Size(), seam_scale, seam_scale);
		images[i] = img.clone();
	}

	finder->collectGarbage();
	full_img.release();
	img.release();

	LOGLN("Finding features, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

	LOG("Pairwise matching");
#if ENABLE_LOG
	t = getTickCount();
#endif
	vector<MatchesInfo> pairwise_matches;
	/*
	struct CV_EXPORTS MatchesInfo
	{
	MatchesInfo();
	MatchesInfo(const MatchesInfo &other);
	const MatchesInfo& operator =(const MatchesInfo &other);

	int src_img_idx, dst_img_idx;       //!< Images indices (optional)
	std::vector<DMatch> matches;
	std::vector<uchar> inliers_mask;    //!< Geometrically consistent matches mask
	int num_inliers;                    //!< Number of geometrically consistent matches
	Mat H;                              //!< Estimated homography
	double confidence;                  //!< Confidence two images are from the same panorama
	};

	class DMatch
	{
		CV_PROP_RW int queryIdx; // query descriptor index
		CV_PROP_RW int trainIdx; // train descriptor index
		CV_PROP_RW int imgIdx;   // train image index
		CV_PROP_RW float distance;

	*/
	Ptr<FeaturesMatcher> matcher;
	if (matcher_type == "affine")
		matcher = makePtr<AffineBestOf2NearestMatcher>(false, try_cuda, match_conf);
	else if (range_width == -1)
		matcher = makePtr<BestOf2NearestMatcher>(try_cuda, match_conf);
	else
		matcher = makePtr<BestOf2NearestRangeMatcher>(range_width, try_cuda, match_conf);

	//从features获取pairwise_matches
	(*matcher)(features, pairwise_matches);
	/*
	查看依次调用：
	这个是可调用对象，应该是重载了operator()；
	但是查看BestOf2NearestMatcher类发现没有重载operator()，于是往上搜，发现
	这个类的基类FeaturesMatcher有重载operator()，
	void operator ()(const std::vector<ImageFeatures> &features, std::vector<MatchesInfo> &pairwise_matches,
	const cv::UMat &mask = cv::UMat());
	在这个函数中，又有一个类MatchPairsBody，也是一个可调用对象，然后判断
	if (is_thread_safe_) 
	void MatchPairsBody::operator ()(const Range &r) const
	MatchPairsBody中的FeaturesMatcher &matcher又是一个可调用对象，调用了
	matcher(features[from], features[to], pairwise_matches[pair_idx]);
	而FeaturesMatcher的operator()调用的是match方法
	void operator ()(const ImageFeatures &features1, const ImageFeatures &features2,
	MatchesInfo& matches_info) { match(features1, features2, matches_info); }
	而此基类的match方法是虚函数=0，这个类是抽象类，所以这个match又调用了
	基类BestOf2NearestMatcher的match方法
	void match(const ImageFeatures &features1, const ImageFeatures &features2, MatchesInfo &matches_info);
	一个很重要的遗漏了，match方法的第二句是(*impl_)(features1, features2, matches_info);
	而这个impl_的类型是Ptr<FeaturesMatcher>，而在BestOf2NearestMatcher的构造函数中有一句
	impl_ = makePtr<CpuMatcher>(match_conf);is_thread_safe_ = impl_->isThreadSafe();
	CpuMatcher是声明和定义在matchers.cpp中的，也继承了FeaturesMatcher，构造函数：
	CpuMatcher(float match_conf) : FeaturesMatcher(true), match_conf_(match_conf) {}
	所以is_thread_safe_ = true；所以其实是先调用了CpuMatcher的match方法，所以呀，这里面有用到KDTree，
	不然匹配都没用到KD树就感觉奇怪呀 
	Ptr<flann::IndexParams> indexParams = makePtr<flann::KDTreeIndexParams>();
	Ptr<flann::SearchParams> searchParams = makePtr<flann::SearchParams>();
	主要是调用了knnMatch方法，这个还暂时看不懂
	*/

	matcher->collectGarbage();

	LOGLN("Pairwise matching, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

	// Check if we should save matches graph
	if (save_graph)
	{
		LOGLN("Saving matches graph...");
		ofstream f(save_graph_to.c_str());
		f << matchesGraphAsString(img_names, pairwise_matches, conf_thresh);
		// Nm代表匹配的数量，NI代表正确匹配的数量，C表示置信度
	}

	// Leave only images we are sure are from the same panorama
	vector<int> indices = leaveBiggestComponent(features, pairwise_matches, conf_thresh);
	/*
	使用查并集法，将图片的匹配关系找出，并删除那些不属于同一全景图的图片.
	并查集用于不相交集合，这个方法其实还是挺巧妙的，如果某两张图片的置信度比较低，
	比如0 1 0.709677 ，表示0和1的置信度为0.7，但是0 7 1.84211 所以最终第一张图片也会加入
	全局的。
	*/

	vector<Mat> img_subset;
	vector<String> img_names_subset;
	vector<Size> full_img_sizes_subset;

	//重新将留下的图像读入
	for (size_t i = 0; i < indices.size(); ++i)
	{
		img_names_subset.push_back(img_names[indices[i]]);
		img_subset.push_back(images[indices[i]]);
		full_img_sizes_subset.push_back(full_img_sizes[indices[i]]);
	}

	images = img_subset;
	img_names = img_names_subset;
	full_img_sizes = full_img_sizes_subset;

	// Check if we still have enough images
	num_images = static_cast<int>(img_names.size());
	if (num_images < 2)
	{
		LOGLN("Need more images");
		return -1;
	}

	Ptr<Estimator> estimator;
	if (estimator_type == "affine")
		estimator = makePtr<AffineBasedEstimator>();
	else
		estimator = makePtr<HomographyBasedEstimator>();
	/*
	@brief Homography based rotation estimator.

	class CV_EXPORTS HomographyBasedEstimator : public Estimator
	{
	public:
	HomographyBasedEstimator(bool is_focals_estimated = false)
	: is_focals_estimated_(is_focals_estimated) {}

	private:
	virtual bool estimate(const std::vector<ImageFeatures> &features,
	const std::vector<MatchesInfo> &pairwise_matches,
	std::vector<CameraParams> &cameras);

	bool is_focals_estimated_;
	*/

	vector<CameraParams> cameras;
	/*
	struct CV_EXPORTS CameraParams
	{
		CameraParams();
		CameraParams(const CameraParams& other);
		const CameraParams& operator =(const CameraParams& other);
		Mat K() const;

		double focal; // Focal length
		double aspect; // Aspect ratio
		double ppx; // Principal point X
		double ppy; // Principal point Y
		Mat R; // Rotation
		Mat t; // Translation
	};
	*/
	//从pairwise_matches获取相机参数
	if (!(*estimator)(features, pairwise_matches, cameras))
	{
		cout << "Homography estimation failed.\n";
		return -1;
	}
	/*
	可以看出HomographyBasedEstimator继承了类Estimator，而estimate方法为虚函数
	};和上面的match一样类HomographyBasedEstimator中没有重载operator()操作符，而
	基类estimate中有调用操作符重载
	bool operator ()(const std::vector<ImageFeatures> &features,
	const std::vector<MatchesInfo> &pairwise_matches,
	std::vector<CameraParams> &cameras)
	{ return estimate(features, pairwise_matches, cameras); } 而类Estimator中的
	estimate方法为纯虚的所以其实还是调用了
	bool HomographyBasedEstimator::estimate(
	const std::vector<ImageFeatures> &features,
	const std::vector<MatchesInfo> &pairwise_matches,
	std::vector<CameraParams> &cameras)：
	首先由之前pairwise_matches中的H估算相机内参矩阵
	——estimateFocal(features, pairwise_matches, focals);
	我一开始比较纳闷，为什么Initial camera intrinsics #的值都是
	一样的，后来看源码才知道，因为取了中位数，理论上16幅图片，至少15
	个H矩阵，然后应该有很多不同的相机参数。
	这里又调用了focalsFromHomography(m.H, f0, f1, f0ok, f1ok);
	关于里面各种h[i]乘来乘去计算f0与f1，可以参考论文
	《Construction of Panoramic Image Mosaics with Global and Local Alignment》
	的第五节，上面有推导公式，其实也蛮简单的。
	当然除了估计相机内参，还有一个旋转外参，这里主要用到了
	findMaxSpanningTree(num_images, pairwise_matches, span_tree, span_tree_centers);
	span_tree.walkBreadthFirst(span_tree_centers[0], 
	CalcRotation(num_images, pairwise_matches, cameras));
	先来说说 最大生成树方法，使用的是kruskal最小生成树算法
	void findMaxSpanningTree(int num_images, const std::vector<MatchesInfo> &pairwise_matches,
	Graph &span_tree, std::vector<int> &centers)
	Graph数据结构其实就是图，用邻接链表表示
	class CV_EXPORTS Graph
	{
	public:
	Graph(int num_vertices = 0) { create(num_vertices); }
	void create(int num_vertices) { edges_.assign(num_vertices, std::list<GraphEdge>()); }
	int numVertices() const { return static_cast<int>(edges_.size()); }
	void addEdge(int from, int to, float weight);
	template <typename B> B forEach(B body) const;
	template <typename B> B walkBreadthFirst(int from, B body) const;
	private:
	std::vector< std::list<GraphEdge> > edges_;
	};
	表示一条有向边
	struct CV_EXPORTS GraphEdge
	{
	GraphEdge(int from, int to, float weight);
	bool operator <(const GraphEdge& other) const { return weight < other.weight; }
	bool operator >(const GraphEdge& other) const { return weight > other.weight; }

	int from, to;
	float weight;
	};
	findMaxSpanningTree：
	由于可能输入多个图像，产生了多个匹配特征点的MatchesInfo结构，
	每个MatchesInfo包含两幅图像之间匹配的特征点(内点)以及H矩阵，
	需要确定这些图像之间的邻接关系，
	这里以两幅图像之间的内点数量为权值构建最大生成树，
	保证这样的一个图片序列两两之间的内点数最多，也就最有可能是邻接的；
	找出节点数为1的结点，以此为根做广度优先遍历，计算每个结点所在的层，
	最终找出最大生成树的中心结点位置。
	用广度优先遍历这棵最大生成树，
	分别计算每两个邻接图像(也就是每个相机)的旋转矩阵R。
	span_tree.walkBreadthFirst:
	原理：
	根据上面的公式：H=K1*R12*K2的逆，R12=K1的逆*H*K2,R1=R2*R12=R2*K1的逆*H*K2，
	已知上幅图像的R、两个相机的内参Ki(焦距、主点)、两幅图的单应矩阵H，
	可以求得下幅图的R。
	*/

	for (size_t i = 0; i < cameras.size(); ++i)
	{
		Mat R;
		cameras[i].R.convertTo(R, CV_32F);
		cameras[i].R = R;
		LOGLN("Initial camera intrinsics #" << indices[i] + 1 << ":\nK:\n" << cameras[i].K() << "\nR:\n" << cameras[i].R);
	}

	Ptr<detail::BundleAdjusterBase> adjuster;
	if (ba_cost_func == "reproj") adjuster = makePtr<detail::BundleAdjusterReproj>();
	else if (ba_cost_func == "ray") adjuster = makePtr<detail::BundleAdjusterRay>();
	/*
	// Minimizes sun of ray-to-ray distances.
	// It can estimate focal length. It ignores the refinement mask for now.
	class CV_EXPORTS BundleAdjusterRay : public BundleAdjusterBase
	{
	public:
	BundleAdjusterRay() : BundleAdjusterBase(4, 3) {}

	private:
	void setUpInitialCameraParams(const std::vector<CameraParams> &cameras);
	void obtainRefinedCameraParams(std::vector<CameraParams> &cameras) const;
	void calcError(Mat &err);
	void calcJacobian(Mat &jac);

	Mat err1_, err2_;
	};


	class CV_EXPORTS BundleAdjusterBase : public Estimator
	{
	public:
	const Mat refinementMask() const { return refinement_mask_.clone(); }
	void setRefinementMask(const Mat &mask)
	{
	CV_Assert(mask.type() == CV_8U && mask.size() == Size(3, 3));
	refinement_mask_ = mask.clone();
	}

	double confThresh() const { return conf_thresh_; }
	void setConfThresh(double conf_thresh) { conf_thresh_ = conf_thresh; }

	CvTermCriteria termCriteria() { return term_criteria_; }
	void setTermCriteria(const CvTermCriteria& term_criteria) { term_criteria_ = term_criteria; }

	protected:
	BundleAdjusterBase(int num_params_per_cam, int num_errs_per_measurement)
	: num_params_per_cam_(num_params_per_cam),
	num_errs_per_measurement_(num_errs_per_measurement)
	{
	setRefinementMask(Mat::ones(3, 3, CV_8U));
	setConfThresh(1.);
	setTermCriteria(cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 1000, DBL_EPSILON));
	}

	// Runs bundle adjustment
	virtual void estimate(const std::vector<ImageFeatures> &features,
	const std::vector<MatchesInfo> &pairwise_matches,
	std::vector<CameraParams> &cameras);

	virtual void setUpInitialCameraParams(const std::vector<CameraParams> &cameras) = 0;
	virtual void obtainRefinedCameraParams(std::vector<CameraParams> &cameras) const = 0;
	virtual void calcError(Mat &err) = 0;
	virtual void calcJacobian(Mat &jac) = 0;

	// 3x3 8U mask, where 0 means don't refine respective parameter, != 0 means refine
	Mat refinement_mask_;

	int num_images_;
	int total_num_matches_;

	int num_params_per_cam_;
	int num_errs_per_measurement_;

	const ImageFeatures *features_;
	const MatchesInfo *pairwise_matches_;

	// Threshold to filter out poorly matched image pairs
	double conf_thresh_;

	//Levenberg–Marquardt algorithm termination criteria
	CvTermCriteria term_criteria_;

	// Camera parameters matrix (CV_64F)
	Mat cam_params_;

	// Connected images pairs
	std::vector<std::pair<int,int> > edges_;
	};
	*/
	else if (ba_cost_func == "affine") adjuster = makePtr<detail::BundleAdjusterAffinePartial>();
	else if (ba_cost_func == "no") adjuster = makePtr<NoBundleAdjuster>();
	else
	{
		cout << "Unknown bundle adjustment cost function: '" << ba_cost_func << "'.\n";
		return -1;
	}
	adjuster->setConfThresh(conf_thresh);
	//// Threshold to filter out poorly matched image pairs

	Mat_<uchar> refine_mask = Mat::zeros(3, 3, CV_8U);
	if (ba_refine_mask[0] == 'x') refine_mask(0, 0) = 1;
	if (ba_refine_mask[1] == 'x') refine_mask(0, 1) = 1;
	if (ba_refine_mask[2] == 'x') refine_mask(0, 2) = 1;
	if (ba_refine_mask[3] == 'x') refine_mask(1, 1) = 1;
	if (ba_refine_mask[4] == 'x') refine_mask(1, 2) = 1;

	// 3x3 8U mask, where 0 means don't refine respective parameter, != 0 means refine
	adjuster->setRefinementMask(refine_mask);
	if (!(*adjuster)(features, pairwise_matches, cameras))
	{
		cout << "Camera parameters adjusting failed.\n";
		return -1;
	}
	/*
	Bundle Adjustment（光束法平差）算法主要是解决所有相机参数的联合。
	这是全景拼接必须的一步，因为多个成对的单应性矩阵合成全景图时，会忽略全局的限制，
	造成累积误差。因此每一个图像都要加上光束法平差值，使图像被初始化成相同的旋转和焦距长度。
	光束法平差的目标函数是一个具有鲁棒性的映射误差的平方和函数。
	即每一个特征点都要映射到其他的图像中，计算出使误差的平方和最小的相机参数

	这里的类BundleAdjusterRay和之前的一样，此类中没有重载operator()，但是它的基类BundleAdjusterBase
	居然也没有，不过BundleAdjusterBase的基类Estimator倒是有的，然后调用了estimate方法，但是此方法在
	Estimator中是纯虚的，所以调用下面的方法，    
	virtual void estimate(const std::vector<ImageFeatures> &features,
	const std::vector<MatchesInfo> &pairwise_matches,
	std::vector<CameraParams> &cameras); 此方法定义在类BundleAdjusterBase中
	在estimate方法中首先调用了setUpInitialCameraParams(cameras);这个过程代码很少，但是原理不懂
	计算cam_params_的值，先初始化cam_params(num_images_*4,1,CV_64F);
	cam_params_[i*4+0] =  cameras[i].focal;cam_params_后面3个值，是cameras[i].R先经过奇异值分解，
	然后对u*vt进行Rodrigues运算，得到的rvec第一行3个值赋给cam_params_。
	奇异值分解的定义：
	在矩阵M的奇异值分解中 M = UΣV*
	·U的列(columns)组成一套对M的正交"输入"或"分析"的基向量。这些向量是MM*的特征向量。
	·V的列(columns)组成一套对M的正交"输出"的基向量。这些向量是M*M的特征向量。
	·Σ对角线上的元素是奇异值，可视为是在输入与输出间进行的标量的"膨胀控制"。
	这些是M*M及MM*的奇异值，并与U和V的行向量相对应。

	CvLevMarq solver(num_images_ * num_params_per_cam_,
	total_num_matches_ * num_errs_per_measurement_,
	term_criteria_);代码看到这里，发现num_params_per_cam_和num_errs_per_measurement_这两个
	参数都没有赋值语句，所以不知道这两个参数的具体值
	*/


	// Find median focal length

	vector<double> focals;
	for (size_t i = 0; i < cameras.size(); ++i)
	{
		LOGLN("Camera #" << indices[i] + 1 << ":\nK:\n" << cameras[i].K() << "\nR:\n" << cameras[i].R);
		focals.push_back(cameras[i].focal);
	}

	sort(focals.begin(), focals.end());
	/*
	现在不知道这个warped_image_scale干嘛的，
	*/
	float warped_image_scale;
	if (focals.size() % 2 == 1)
		warped_image_scale = static_cast<float>(focals[focals.size() / 2]);
	else
		warped_image_scale = static_cast<float>(focals[focals.size() / 2 - 1] + focals[focals.size() / 2]) * 0.5f;

	if (do_wave_correct)
	{
		vector<Mat> rmats;
		for (size_t i = 0; i < cameras.size(); ++i)
			rmats.push_back(cameras[i].R.clone());
		waveCorrect(rmats, wave_correct);
		for (size_t i = 0; i < cameras.size(); ++i)
			cameras[i].R = rmats[i];
	}

	LOGLN("Warping images (auxiliary)... ");
#if ENABLE_LOG
	t = getTickCount();
#endif

	vector<Point> corners(num_images);
	vector<UMat> masks_warped(num_images);
	vector<UMat> images_warped(num_images);
	vector<Size> sizes(num_images);
	vector<UMat> masks(num_images);

	// Preapre images masks
	for (int i = 0; i < num_images; ++i)
	{
		masks[i].create(images[i].size(), CV_8U);
		masks[i].setTo(Scalar::all(255));
	}

	// Warp images and their masks

	Ptr<WarperCreator> warper_creator;
#ifdef HAVE_OPENCV_CUDAWARPING
	if (try_cuda && cuda::getCudaEnabledDeviceCount() > 0)
	{
		if (warp_type == "plane")
			warper_creator = makePtr<cv::PlaneWarperGpu>();
		else if (warp_type == "cylindrical")
			warper_creator = makePtr<cv::CylindricalWarperGpu>();
		else if (warp_type == "spherical")
			warper_creator = makePtr<cv::SphericalWarperGpu>();
	}
	else
#endif
	{
		if (warp_type == "plane")
			warper_creator = makePtr<cv::PlaneWarper>();
		else if (warp_type == "affine")
			warper_creator = makePtr<cv::AffineWarper>();
		else if (warp_type == "cylindrical")
			warper_creator = makePtr<cv::CylindricalWarper>();
		else if (warp_type == "spherical")
			warper_creator = makePtr<cv::SphericalWarper>();
		else if (warp_type == "fisheye")
			warper_creator = makePtr<cv::FisheyeWarper>();
		else if (warp_type == "stereographic")
			warper_creator = makePtr<cv::StereographicWarper>();
		else if (warp_type == "compressedPlaneA2B1")
			warper_creator = makePtr<cv::CompressedRectilinearWarper>(2.0f, 1.0f);
		else if (warp_type == "compressedPlaneA1.5B1")
			warper_creator = makePtr<cv::CompressedRectilinearWarper>(1.5f, 1.0f);
		else if (warp_type == "compressedPlanePortraitA2B1")
			warper_creator = makePtr<cv::CompressedRectilinearPortraitWarper>(2.0f, 1.0f);
		else if (warp_type == "compressedPlanePortraitA1.5B1")
			warper_creator = makePtr<cv::CompressedRectilinearPortraitWarper>(1.5f, 1.0f);
		else if (warp_type == "paniniA2B1")
			warper_creator = makePtr<cv::PaniniWarper>(2.0f, 1.0f);
		else if (warp_type == "paniniA1.5B1")
			warper_creator = makePtr<cv::PaniniWarper>(1.5f, 1.0f);
		else if (warp_type == "paniniPortraitA2B1")
			warper_creator = makePtr<cv::PaniniPortraitWarper>(2.0f, 1.0f);
		else if (warp_type == "paniniPortraitA1.5B1")
			warper_creator = makePtr<cv::PaniniPortraitWarper>(1.5f, 1.0f);
		else if (warp_type == "mercator")
			warper_creator = makePtr<cv::MercatorWarper>();
		else if (warp_type == "transverseMercator")
			warper_creator = makePtr<cv::TransverseMercatorWarper>();
	}

	if (!warper_creator)
	{
		cout << "Can't create the following warper '" << warp_type << "'\n";
		return 1;
	}

	Ptr<RotationWarper> warper = warper_creator->create(static_cast<float>(warped_image_scale * seam_work_aspect));

	for (int i = 0; i < num_images; ++i)
	{
		Mat_<float> K;
		cameras[i].K().convertTo(K, CV_32F);
		float swa = (float)seam_work_aspect;
		K(0, 0) *= swa; K(0, 2) *= swa;
		K(1, 1) *= swa; K(1, 2) *= swa;

		corners[i] = warper->warp(images[i], K, cameras[i].R, INTER_LINEAR, BORDER_REFLECT, images_warped[i]);
		sizes[i] = images_warped[i].size();

		warper->warp(masks[i], K, cameras[i].R, INTER_NEAREST, BORDER_CONSTANT, masks_warped[i]);
	}

	vector<UMat> images_warped_f(num_images);
	for (int i = 0; i < num_images; ++i)
		images_warped[i].convertTo(images_warped_f[i], CV_32F);

	LOGLN("Warping images, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

	Ptr<ExposureCompensator> compensator = ExposureCompensator::createDefault(expos_comp_type);
	compensator->feed(corners, images_warped, masks_warped);

	Ptr<SeamFinder> seam_finder;
	if (seam_find_type == "no")
		seam_finder = makePtr<detail::NoSeamFinder>();
	else if (seam_find_type == "voronoi")
		seam_finder = makePtr<detail::VoronoiSeamFinder>();
	else if (seam_find_type == "gc_color")
	{
#ifdef HAVE_OPENCV_CUDALEGACY
		if (try_cuda && cuda::getCudaEnabledDeviceCount() > 0)
			seam_finder = makePtr<detail::GraphCutSeamFinderGpu>(GraphCutSeamFinderBase::COST_COLOR);
		else
#endif
			seam_finder = makePtr<detail::GraphCutSeamFinder>(GraphCutSeamFinderBase::COST_COLOR);
	}
	else if (seam_find_type == "gc_colorgrad")
	{
#ifdef HAVE_OPENCV_CUDALEGACY
		if (try_cuda && cuda::getCudaEnabledDeviceCount() > 0)
			seam_finder = makePtr<detail::GraphCutSeamFinderGpu>(GraphCutSeamFinderBase::COST_COLOR_GRAD);
		else
#endif
			seam_finder = makePtr<detail::GraphCutSeamFinder>(GraphCutSeamFinderBase::COST_COLOR_GRAD);
	}
	else if (seam_find_type == "dp_color")
		seam_finder = makePtr<detail::DpSeamFinder>(DpSeamFinder::COLOR);
	else if (seam_find_type == "dp_colorgrad")
		seam_finder = makePtr<detail::DpSeamFinder>(DpSeamFinder::COLOR_GRAD);
	if (!seam_finder)
	{
		cout << "Can't create the following seam finder '" << seam_find_type << "'\n";
		return 1;
	}

	seam_finder->find(images_warped_f, corners, masks_warped);

	// Release unused memory
	images.clear();
	images_warped.clear();
	images_warped_f.clear();
	masks.clear();

	LOGLN("Compositing...");
#if ENABLE_LOG
	t = getTickCount();
#endif

	Mat img_warped, img_warped_s;
	Mat dilated_mask, seam_mask, mask, mask_warped;
	Ptr<Blender> blender;
	Ptr<Timelapser> timelapser;
	//double compose_seam_aspect = 1;
	double compose_work_aspect = 1;

	for (int img_idx = 0; img_idx < num_images; ++img_idx)
	{
		LOGLN("Compositing image #" << indices[img_idx] + 1);

		// Read image and resize it if necessary
		full_img = imread(img_names[img_idx]);
		if (!is_compose_scale_set)
		{
			if (compose_megapix > 0)
				compose_scale = min(1.0, sqrt(compose_megapix * 1e6 / full_img.size().area()));
			is_compose_scale_set = true;

			// Compute relative scales
			//compose_seam_aspect = compose_scale / seam_scale;
			compose_work_aspect = compose_scale / work_scale;

			// Update warped image scale
			warped_image_scale *= static_cast<float>(compose_work_aspect);
			warper = warper_creator->create(warped_image_scale);

			// Update corners and sizes
			for (int i = 0; i < num_images; ++i)
			{
				// Update intrinsics
				cameras[i].focal *= compose_work_aspect;
				cameras[i].ppx *= compose_work_aspect;
				cameras[i].ppy *= compose_work_aspect;

				// Update corner and size
				Size sz = full_img_sizes[i];
				if (std::abs(compose_scale - 1) > 1e-1)
				{
					sz.width = cvRound(full_img_sizes[i].width * compose_scale);
					sz.height = cvRound(full_img_sizes[i].height * compose_scale);
				}

				Mat K;
				cameras[i].K().convertTo(K, CV_32F);
				Rect roi = warper->warpRoi(sz, K, cameras[i].R);
				corners[i] = roi.tl();
				sizes[i] = roi.size();
			}
		}
		if (abs(compose_scale - 1) > 1e-1)
			resize(full_img, img, Size(), compose_scale, compose_scale);
		else
			img = full_img;
		full_img.release();
		Size img_size = img.size();

		Mat K;
		cameras[img_idx].K().convertTo(K, CV_32F);

		// Warp the current image
		warper->warp(img, K, cameras[img_idx].R, INTER_LINEAR, BORDER_REFLECT, img_warped);

		// Warp the current image mask
		mask.create(img_size, CV_8U);
		mask.setTo(Scalar::all(255));
		warper->warp(mask, K, cameras[img_idx].R, INTER_NEAREST, BORDER_CONSTANT, mask_warped);

		// Compensate exposure
		compensator->apply(img_idx, corners[img_idx], img_warped, mask_warped);

		img_warped.convertTo(img_warped_s, CV_16S);
		img_warped.release();
		img.release();
		mask.release();

		dilate(masks_warped[img_idx], dilated_mask, Mat());
		resize(dilated_mask, seam_mask, mask_warped.size());
		mask_warped = seam_mask & mask_warped;

		if (!blender && !timelapse)
		{
			blender = Blender::createDefault(blend_type, try_cuda);
			Size dst_sz = resultRoi(corners, sizes).size();
			float blend_width = sqrt(static_cast<float>(dst_sz.area())) * blend_strength / 100.f;
			if (blend_width < 1.f)
				blender = Blender::createDefault(Blender::NO, try_cuda);
			else if (blend_type == Blender::MULTI_BAND)
			{
				MultiBandBlender* mb = dynamic_cast<MultiBandBlender*>(blender.get());
				mb->setNumBands(static_cast<int>(ceil(log(blend_width) / log(2.)) - 1.));
				LOGLN("Multi-band blender, number of bands: " << mb->numBands());
			}
			else if (blend_type == Blender::FEATHER)
			{
				FeatherBlender* fb = dynamic_cast<FeatherBlender*>(blender.get());
				fb->setSharpness(1.f / blend_width);
				LOGLN("Feather blender, sharpness: " << fb->sharpness());
			}
			blender->prepare(corners, sizes);
		}
		else if (!timelapser && timelapse)
		{
			timelapser = Timelapser::createDefault(timelapse_type);
			timelapser->initialize(corners, sizes);
		}

		// Blend the current image
		if (timelapse)
		{
			timelapser->process(img_warped_s, Mat::ones(img_warped_s.size(), CV_8UC1), corners[img_idx]);
			String fixedFileName;
			size_t pos_s = String(img_names[img_idx]).find_last_of("/\\");
			if (pos_s == String::npos)
			{
				fixedFileName = "fixed_" + img_names[img_idx];
			}
			else
			{
				fixedFileName = "fixed_" + String(img_names[img_idx]).substr(pos_s + 1, String(img_names[img_idx]).length() - pos_s);
			}
			imwrite(fixedFileName, timelapser->getDst());
		}
		else
		{
			blender->feed(img_warped_s, mask_warped, corners[img_idx]);
		}
	}

	if (!timelapse)
	{
		Mat result, result_mask;
		blender->blend(result, result_mask);

		LOGLN("Compositing, time: " << ((getTickCount() - t) / getTickFrequency()) << " sec");

		imwrite(result_name, result);
	}

	LOGLN("Finished, total time: " << ((getTickCount() - app_start_time) / getTickFrequency()) << " sec");
	return 0;
}
