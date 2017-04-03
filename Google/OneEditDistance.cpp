// https://discuss.leetcode.com/category/169/one-edit-distance
bool isOneEditDistance (const std::string & left,
                        const std::string & right) {
  const std::size_t left_size(left.size()), right_size(right.size());
  // make sure size difference <= 1
  if (std::max(left_size, right_size) - std::min(left_size,right_size) > 1)
    return false;
  int mismatch(0); // make sure only one mistach is allowed
  std::size_t left_index(0), right_index(0);
  while ( left_index < left_size && right_index < right_size ) {
    if (left[left_index] != right[right_index]) { // mismatch
      if (mismatch > 0) return false;
      ++ mismatch;
      if (left_size == right_size) {
        ++ left_index, ++ right_index;
      } else if (left_size > right_size) {
        ++ left_index;
      } else {
        ++ right_index;
      }
    } else { // match
      ++ left_index, ++ right_index;
    }
  }
  // (abc, aBcd)
  return (left_index == left_size && right_index == right_size) || mismatch == 0;
}

void UnitTest() {
  assert(isOneEditDistance("abc","aBc") == true);
  assert(isOneEditDistance("abcd","acd") == true);
  assert(isOneEditDistance("acc","accd") == true);
  assert(isOneEditDistance("aaa","aaAa") == true);

  assert(isOneEditDistance("abc","aBC") == false);
  assert(isOneEditDistance("aaaA","aaAa") == false);
  assert(isOneEditDistance("abcd","aBCd") == false);
  assert(isOneEditDistance("abc","aecd") == false);
}
