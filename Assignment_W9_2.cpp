#include<iostream>
#include<string>

using namespace std;
//Định nghĩa cấu trúc 1 node
struct node {
	string tu;
	int dem;
	node* next;
};
//Hàm tạo một node
node* createnode(string& a) {
	node* newnode = new node;
	newnode->tu = a;
	newnode->dem = 1;
	newnode->next = NULL;
	return newnode;
}
//Hàm định nghĩa danh sách liên kết 
struct List {
	node* head;
};
//Hàm tạo danh sách liên kết
void initializeList(List& list) {
	list.head = NULL;
}
//Thêm phần tử vào danh sách liên kết
void themtu(List& list, string& word) {
	node* current = list.head;
	
	while (current != NULL) {
		current = current->next;
	}

	node* newnode = createnode(word);  
	if (list.head == NULL) {            
		list.head = newnode;
	}
	else {
		node* last = list.head;
		while (last->next != NULL) {   
			last = last->next;
		}
		last->next = newnode;          
	}
}

//Hàm tìm từ xuất hiện nhiều nhất
string xuathien(List& list) {
	node* current = list.head;
	string max;
	int count = 0;
	while (current != NULL) {
		if (current->dem > count) {
			count = current->dem;
			max = current->tu;
		}
		current = current->next;
	}
	return max;
}

// Hàm loại bỏ từ láy
void loaibo(List& list) {
	node* current = list.head;
	node* prev = NULL;

	while (current != NULL) {
		// Kiểm tra nếu có từ láy (node hiện tại giống node trước đó)
		if (prev != NULL && current->tu == prev->tu) {
			prev->next = current->next;   // Bỏ qua node hiện tại
			delete current;               // Giải phóng bộ nhớ của node bị loại bỏ
			current = prev->next;         // Di chuyển current đến node tiếp theo
		}
		else {
			prev = current;               // Cập nhật prev
			current = current->next;      // Di chuyển đến node tiếp theo
		}
	}
}


//Hàm đếm số từ vựng trong câu
int sotuvung(List& list) {
	int count = 0;
	node* current = list.head;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}
// Hàm in câu (In danh sách liên kết)
void in(List& list) {
	node* current = list.head;
	while (current != NULL) {
		cout << current->tu << " ";
		current = current->next;
	}
}

//Giải phóng dung lượng bộ nhớ
void deleteList(List& list) {
	node* current = list.head;
	while (current != NULL) {
		node* temp = current;
		current = current->next;
		delete temp;
	}
	list.head = NULL;
}

int main() {
	List list;
	initializeList(list);
	string a;
	do {
		cout << "Nhap vao lan luot cac tu trong cau (Nhap '.' de ket thuc): ";
		cin >> a;
		if (a != ".") {
			themtu(list, a);
		}
	} while (a != ".");
	cout << "Cau da nhap: ";
	in(list);
	cout << endl;
	cout << "Tu xuat hien nhieu nhat: " << xuathien(list) << endl;
	cout << "So tu trong cau: " << sotuvung(list) << endl;
	loaibo(list);
	cout << "Cau sau khi loai bo tu lay: ";
	in(list);
	deleteList(list);

	return 0;

}