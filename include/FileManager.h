#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

class FileManager {
public:
  // constructor: tell it where to save files
  FileManager(const std::string &upload_folder);

  // save file safely and return true if successful
  bool save_file(const std::string &filename, const std::string &file_content);

private:
  fs::path upload_dir;
};
