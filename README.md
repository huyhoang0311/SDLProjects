### GAME INT2215 50: BLEACH VS NARUTO 2.0 - Made by Trần Hữu Huy Hoàng  

## Author Information
Họ tên: Trần Hữu Huy Hoàng </br>
Mã số sinh viên: 23020073

## IDEA:
Dựa trên game Bleach vs Naruto (đối kháng 2 người) 

## THAM KHẢO:
Phattrienphanmem123az Tutorials: https://www.youtube.com/watch?v=k1JGvJU707k&list=PLR7NDiX0QsfQQ2iFXsXepwH46wf3D4Y4C
SDL2.0: https://www.libsdl.org
Lazyfoo Productions: https://lazyfoo.net/tutorials/SDL/index.php
Đồ họa: 
- Nhân vật: https://itch.io , phattrienphanmem123az.com, thiết kế riêng của em 
- Background: Pinterest
- Đạn: Itch.io

//Phần code game (code nhân vật) được em tham khảo khá nhiều từ Phattrienphanmem123az Tutorials </br>
  Code của em đã upgrade thêm 1 số phần để phát triển từ Phattrienphanmem123az Tutorials -> Game đối kháng 2 người như xử lý va chạm 2 người, tối ưu hóa bộ nhớ, xử lý thanh máu, menu,.

## CÁCH MỞ
Step 1: Clone repo / Dowload file zip </br>
Step 2: Setting Microsoft Visual Studio và SDL2.0 </br>
Step 3: Open main.cpp by Visual Studio và build project</br>
Step 4: Enjoy </br>

## CÁCH CHƠI
# INGAME:
Player 1:
A, D: Di chuyển trái phải.
K: Nhảy </br>
J:  Bắn đạn (normal) </br>
Khi máu (health) của nhân vật dưới 50% -> có thể nhấn O: tiến vào trạng thái demon
Khi ở trạng thái demon:
U: Bắn đạn (demon) </br>
L: Dịch chuyển tức thời


Player 2:
Phím trái, phải: Di chuyển trái phải.
Phím 2: Nhảy </br>
Phím 1:  Bắn đạn (normal) </br>
Khi máu (health) của nhân vật dưới 50% -> có thể nhấn 3: tiến vào trạng thái demon
Khi ở trạng thái demon:
U: Mưa đạn (demon) </br>


Nhấn SPACE để dừng game -> vào PAUSE_STATE


## MAIN FUNCTION
Một vài main function được dùng trong game:
- Menu: Play game, Exit, Replay
- Control 2 player (hàm chuyển động, check va chạm với map) //Tham khảo nguồn Phattrienphanmem123az/
- Xử lý thêm cho 2 player (hàm va chạm giữa 2 người và đạn, hàm biến hình, va chạm giữa đạn và đạn, hàm xử lý thanh máu)
- Pause Game

## SOME BUGS
- Đồ họa đang tương đối sơ sài
- Chưa xử lý được va chạm giữa đạn với map
## UPCOMING UPGRADES
1. Chọn nhân vật
2. Chọn map.
3. Chọn vũ khí.
4. Hiệu ứng nổ, âm thanh, hiệu ứng cho trạng thái demon
DEMO GAME: 
## Contact:
Link github: (https://github.com/huyhoang0311/SDLProjects)
📧 mail: tranhuuhuyhoang3017@gmail.com
