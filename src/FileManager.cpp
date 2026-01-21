#include "../include/FileManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// constructor
FileManager::FileManager(const std::string &upload_folder) {
  upload_dir = upload_folder;
  if (!fs::exists(upload_dir)) {
    fs::create_directory(upload_folder);
  }
}

bool FileManager::save_file(const std::string &filename,
                            const std::string &file_content) {
  auto full_path{upload_dir / filename};

  std::ofstream file(full_path, std::ios::binary);
  if (file.is_open()) {
    file << file_content;
    file.close();
    return true;
  }

  return false;
}
