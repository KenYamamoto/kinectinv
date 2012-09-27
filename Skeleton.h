#include <Windows.h>
#include <NuiApi.h>
#include <opencv2\opencv.hpp>

class Skeleton
{
private:

public:
	Skeleton(void);
	void Skeleton::SetJointsXY(NUI_SKELETON_DATA* skeleton);
	void Skeleton::DrawSkeleton(IplImage* img, NUI_SKELETON_DATA* skeleton, int id);
	void Skeleton::DrawSkeletonLine(IplImage* img, CvPoint st, CvPoint ed );
};

