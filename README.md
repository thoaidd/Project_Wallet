# Project_Wallet
Dự án xây dựng một hệ thống đăng nhập, đăng ký tài khoản và quản lý ví điểm thưởng
## 👥 Thành viên tham gia
| Họ tên         | MSSV       | Vai trò trong nhóm                    |
|----------------|------------|---------------------------------------|
| Đoàn Đình Thoại   | B16DCVT293   | Viết chức năng đăng ký, đăng nhập     |
| Trần Thị B     | 23456789   | Viết chức năng ví điểm thưởng         |


## 📋 Phân tích & đặc tả chức năng
- Đăng ký tài khoản, tạo dữ liệu tài khoản
- Lưu trữ dữ liệu vào file, sao lưu dữ liệu
- Đăng nhập hệ thống
- Quản lý mật khẩu (tự sinh, đổi mật khẩu)
- Xác thực OTP (cho cập nhật thông tin, giao dịch)
- Quản lý điểm ví, chuyển điểm, kiểm tra số dư
- Phân quyền người dùng: người thường / người quản lý

## 📦 Cách tải chương trình
1. Tải mã nguồn về từ GitHub (nếu có repo):
   ```bash
   git clone https://github.com/thoaidd/Project_Wallet
   ```
2. Mở file `main.cpp` trong phần mềm Dev C++ hoặc Code::Blocks
3. Dự án không cần thư viện ngoài. Toàn bộ file `.cpp` và `.h` đều trong thư mục chính.

## 🔧 Cách dịch chương trình
- Mở file `main.cpp` trong Dev C++ (Windows)
- Nhấn `F9` hoặc `Compile & Run`
- Kiểm tra các file `users/`, `wallets/`, `logs/` sẽ được tạo tự động

## ▶️ Hướng dẫn sử dụng
1. Chạy chương trình → Hiện menu chính
2. Đăng ký hoặc đăng nhập
3. Sau khi đăng nhập:
   - Xem ví điểm
   - Thực hiện chuyển điểm (có xác nhận OTP)
   - Thay đổi mật khẩu
   - Người quản lý có thêm quyền tạo tài khoản và xem danh sách người dùng

## 📚 Nguồn tham khảo
- Giáo trình của GV bộ môn.
- ChatGPT.
- Tài liệu lập trình C++ trên [cplusplus.com](http://www.cplusplus.com/)
