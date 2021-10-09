#ifndef HDC_DRIVER_H
#define HDC_DRIVER_H

namespace hdc {
    class Driver {
        public:
            Driver();

        private:
            std::vector<std::string> get_files_from_dir(std::string path);

        private:
            char path_delimiter;
            std::string main_file_path;
            std::string root_path;
            std::string output_name;
            std::vector<std::string> search_path;
    };
}

#endif
