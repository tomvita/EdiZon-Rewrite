#include "file.hpp"

namespace edz::helper {
        File::File(std::string filePath) : m_filePath(filePath) {
            m_file = nullptr;
        }

        File::File(const File &file) {
            this->m_file = file.m_file;
            this->m_filePath = file.m_filePath;
        }

        File::~File() {
            closeFile();
        }
        

        std::string File::fileName() {
            return std::filesystem::path(m_filePath).filename();
        }

        std::string File::path() {
            return m_filePath;
        }

        size_t File::fileSize() {
            openFile();

            if (!valid()) return -1;

            size_t fileSize;
            fseek(m_file, 0, SEEK_END);
            fileSize = ftell(m_file);
            rewind(m_file);

            return fileSize;
        }

        void File::removeFile() {
            openFile();
            if (!valid()) return;
            closeFile();

            remove(m_filePath.c_str());
        }

        void File::copyTo(std::string path) {

            FILE *dst = fopen(path.c_str(), "w");

            size_t size = 0;
            u64 offset = 0;
            u8 *buffer = new u8[0x50000];

            openFile();

            while ((size = fread(buffer, 1, 0x50000, m_file)) > 0) {
                fwrite(buffer, 1, size, dst);
                offset += size;
            }
            
            delete[] buffer;

            closeFile();
            fclose(dst);
        }

        bool File::valid() {
            openFile();

            if (m_file != nullptr) {
                closeFile();
                return true;
            }

            return false;
        }

        s32 File::read(u8 *buffer, size_t bufferSize) {
            size_t readSize = 0;
            
            openFile();
            readSize = fread(buffer, 1, bufferSize, m_file);
            closeFile();

            return readSize;
        }

        s32 File::write(u8 *buffer, size_t bufferSize) {
            size_t writeSize = 0;

            openFile();
            writeSize = fwrite(buffer, 1, bufferSize, m_file);
            closeFile();

            return writeSize;            
        }


        void File::openFile() {
            if (m_file != nullptr) return;

            m_file = fopen(m_filePath.c_str(), "rb");

            if (m_file == nullptr)
                m_file = fopen(m_filePath.c_str(), "w+");
        }

        void File::closeFile() {
            if (m_file == nullptr) return;

            fclose(m_file);
            m_file = nullptr;

        }
}