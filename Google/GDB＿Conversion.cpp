// RGB颜色转换比如现有#2f3d13，有16进制的00,33,66,99，cc, ff.要把现有的数字转成最close to这几个数字。比如#2f3d13 -> #333300；. 
// http://www.1point3acres.com/bbs/thread-177167-1-1.html

int getHexValue(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
  if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
  return 0;
}

std::string RGBChunkConvert(const std::string & str) {
  static std::vector<std::string> numbers = {"00","33","66","99","cc","ff"};
  static const int hex_base(51); // 上面都是 0x33 的倍数, 0x33 = 51
  int val = getHexValue(str[0]) * 16 + getHexValue(str[1]);
  int index = ( (val + 51 / 2) / 51 );
  return numbers[index];
}


std::string RGBConversion(const std::string & rgb) {
  const std::size_t rgb_size(rgb.size());
  if (rgb_size != 7) return "";
  std::ostringstream oss;
  oss << '#';
  for (std::size_t i = 1; i < rgb_size; i += 2) {
    oss << RGBChunkConvert(rgb.substr(i,2));
  }
  return oss.str();
}

void UnitTest() {
  assert(RGBChunkConvert("2f") == "33");
  assert(RGBChunkConvert("3d") == "33");
  assert(RGBChunkConvert("13") == "00");

  assert(RGBConversion("#2f3d13") == "#333300");
}
