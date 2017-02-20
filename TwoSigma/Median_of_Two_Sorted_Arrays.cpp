class Solution {
public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    const std::size_t size1(nums1.size()), size2(nums2.size());

    if (size1 > size2) return findMedianSortedArrays(nums2, nums1);

    // Notice plus one here, so that if the total size is 5, we set
    // left size to be 3, and right size to be 2
    const std::size_t half_size = size1 + (size2 - size1 + 1) / 2;

    // len1 and len2 represents the length of elements we take from
    // vector to constitute the left array
    std::size_t len1(0),len2(0);
    // low and high represents the min and max length of elements we
    // take from nums1 to put into the left array
    std::size_t low(0), high(size1);

    // the important 4 elements:
    // nums1[len1-1],nums1[len1],nums2[len2-1],nums2[len2]
    while (low <= high) {
      len1 = low + (high - low) / 2;
      len2 = half_size - len1;

      if ( len1 < size1 && nums1[len1] < nums2[len2 - 1]) {
        low = len1 + 1;
      } else if (len1 >= 1 && nums1[len1 - 1] > nums2[len2]) {
        high = len1 - 1;
      } else {
        break;
      }
    }

    int max_of_left(0);
    if (len1 == 0) { // no left elements come from nums1
      max_of_left = nums2[len2 - 1];
    } else if (len2 == 0) { // no left elements come from nums2
      max_of_left = nums1[len1 - 1];
    } else { // left elements come from both vector
      max_of_left = std::max(nums1[len1 - 1],nums2[len2 - 1]);
    }

    if ( (size1 + size2) % 2 == 1)
      return max_of_left;

    int min_of_right(0);
    if (len1 == size1) { // no right elements come from nums1
      min_of_right = nums2[len2];
    } else if (len2 == size2) { //  no right elements come from nums2
      min_of_right = nums1[len1 ];
    } else { // right elements come from both vector
      min_of_right = std::min(nums1[len1],nums2[len2]);
    }

    return max_of_left + (min_of_right - max_of_left) / 2.0 ;
  }
};
