#include "../include/FileManager.h"
#include "crow_all.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  crow::SimpleApp app;
  std::string upload_folder{"../upload"};

  // FileManager instance
  FileManager fm(upload_folder);
  namespace fs = std::filesystem;

  CROW_ROUTE(app, "/download/<string>")(
      [](const crow::request &req, const std::string &file_name) {
        std::string full_path{"../upload/" + file_name};
        if (!fs::exists(full_path)) {
          return crow::response(404);
        }

        std::ifstream in_file(full_path);
        std::stringstream ss{};
        ss << in_file.rdbuf();

        crow::response res(ss.str());
        res.set_header("Content-Type", "application/pdf");
        return res;
      });

  CROW_ROUTE(app, "/")([]() {
    std::ifstream in_file("../index.html");
    std::stringstream ss{};
    ss << in_file.rdbuf();
    return ss.str();
  });

  CROW_ROUTE(app, "/upload")
      .methods(crow::HTTPMethod::Post)([&fm](const crow::request &req) {
        auto now{std::chrono::system_clock::now()};
        auto timestamp{std::chrono::duration_cast<std::chrono::seconds>(
                           now.time_since_epoch())
                           .count()};
        std::string file_name{"upload_" + std::to_string(timestamp) + ".pdf"};
        fm.save_file(file_name, req.body);

        return crow::response(200);
      });

  app.port(8080).multithreaded().run();
}
