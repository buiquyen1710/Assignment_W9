#include <iostream>
#include <string>

using namespace std;

// Cấu trúc để lưu thông tin về một file
struct File {
    string name;
    long size;
    long timestamp;
    File* next;
};

// Cấu trúc danh sách liên kết
struct FileList {
    File* head;
};

// Hàm khởi tạo danh sách liên kết
void initializeList(FileList& list) {
    list.head = nullptr;
}

// Hàm thêm một file vào danh sách theo thứ tự thời gian (timestamp)
void insertFile(FileList& list, const string& name, long size, long timestamp) {
    File* newFile = new File;
    newFile->name = name;
    newFile->size = size;
    newFile->timestamp = timestamp;
    newFile->next = nullptr;


    if (list.head == nullptr || list.head->timestamp > timestamp) {
        newFile->next = list.head;
        list.head = newFile;
        return;
    }

    File* current = list.head;
    while (current->next != nullptr && current->next->timestamp < timestamp) {
        current = current->next;
    }

    newFile->next = current->next;
    current->next = newFile;
}

// Hàm tính tổng kích thước các file trong danh sách
long calculateTotalSize(FileList& list) {
    long totalSize = 0;
    File* current = list.head;
    while (current != nullptr) {
        totalSize += current->size;
        current = current->next;
    }
    return totalSize;
}

// Hàm sao lưu các file vào ổ USB (xóa các file nhỏ nhất nếu cần)
void backupToUSB(FileList& list, long usbSize) {
    long totalSize = calculateTotalSize(list);

    while (totalSize > usbSize) {
        if (list.head == nullptr) {
            cout << "Không còn file để loại bỏ.\n";
            return;
        }

        File* current = list.head;
        File* prev = nullptr;
        File* minFile = list.head;
        File* minPrev = nullptr;

        while (current != nullptr) {
            if (current->size < minFile->size) {
                minFile = current;
                minPrev = prev;
            }
            prev = current;
            current = current->next;
        }

        // Loại bỏ file nhỏ nhất
        if (minPrev == nullptr) {
            list.head = minFile->next;
        }
        else {
            minPrev->next = minFile->next;
        }

        delete minFile;
        totalSize = calculateTotalSize(list);
    }

    cout << "Đã sao lưu thành công. Tổng kích thước các file trong thư mục là " << totalSize << " bytes.\n";
}

int main() {
    FileList fileList;  // Khởi tạo danh sách file
    initializeList(fileList);  // Khởi tạo danh sách liên kết

    int n;
    cout << "Nhập số lượng file: ";
    cin >> n;

    // Lặp để nhập thông tin các file từ người dùng
    for (int i = 0; i < n; i++) {
        string name;
        long size, timestamp;

        // Nhập thông tin file
        cout << "Nhập tên file thứ " << i + 1 << ": ";
        cin.ignore();
        getline(cin, name);

        cout << "Nhập kích thước file thứ " << i + 1 << " (bytes): ";
        cin >> size;

        cout << "Nhập thời gian tạo file thứ " << i + 1 << " (timestamp): ";
        cin >> timestamp;

        // Chèn file vào danh sách
        insertFile(fileList, name, size, timestamp);
    }

    // Tính tổng kích thước các file
    cout << "Tổng kích thước các file trong thư mục: " << calculateTotalSize(fileList) << " bytes\n";

    // Sao lưu vào ổ USB 32GB
    long usbSize = 32L * 1024 * 1024 * 1024; // 32GB
    backupToUSB(fileList, usbSize);

    return 0;
}
