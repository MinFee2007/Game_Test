#include <SDL3/SDL_main.h>
#include "src/system_all.h"
#include "src/system_ecs.h"
#include "src/system_event.h"
#include "src/system_time.h"
#include "src/system_resource.h"
#include "src/system_gui.h"
#include "src/system_scene.h"
#include "src/system_manager.h"

int main(int argc, char* argv[]){
    AllSystem& allsystem=AllSystem::getInstance();
    allsystem.addSubSystem<EntityComponentSystem>();
    allsystem.addSubSystem<EventSystem>();
    allsystem.addSubSystem<TimeSystem>();
    allsystem.addSubSystem<ResourceSystem>();
    allsystem.addSubSystem<GUISystem>();
    allsystem.addSubSystem<SceneSystem>();
    allsystem.addSubSystem<ManagerSystem>();
    allsystem.init();
    allsystem.run();
    allsystem.destruct();
    return 0;
}

// int main(int argc, char* argv[]) {
//     // 1. Khởi tạo SDL3 và thư viện ảnh
//     if (!SDL_Init(SDL_INIT_VIDEO)) {
//         SDL_Log("SDL_Init thất bại: %s", SDL_GetError());
//         return 1;
//     }

//     SDL_Window* window = nullptr;
//     SDL_Renderer* renderer = nullptr;

//     // 2. Tạo cửa sổ 800x600 và Renderer
//     if (!SDL_CreateWindowAndRenderer("SDL3 Dynamic Rotation", 800, 600, 0, &window, &renderer)) {
//         SDL_Log("Tạo cửa sổ/renderer thất bại: %s", SDL_GetError());
//         SDL_Quit();
//         return 1;
//     }

//     // 3. Nạp Texture ảnh (ví dụ: ảnh con rồng nhỏ)
//     // Hãy chắc chắn bạn có file 'dragon.png' trong cùng thư mục chạy
//     SDL_Texture* texture = IMG_LoadTexture(renderer, "assets/dragon.jpg");
//     if (!texture) {
//         SDL_Log("Không thể nạp ảnh 'dragon.png': %s", SDL_GetError());
//         SDL_DestroyRenderer(renderer);
//         SDL_DestroyWindow(window);
//         return 1;
//     }

//     // Lấy kích thước ảnh gốc
//     float texW, texH;
//     SDL_GetTextureSize(texture, &texW, &texH);

//     // Xác định vị trí và kích thước vẽ trên màn hình (SDL_FRect)
//     SDL_FRect dstRect = { 336.0f, 236.0f, texW, texH }; // Căn giữa 800x600

//     bool running = true;
//     SDL_Event event;

//     // Các biến cho việc xoay ảnh
//     float currentAngle = 45.0f;          // Góc xoay ban đầu (độ)
//     float rotationSpeed = 180.0f;       // Tốc độ xoay (độ trên giây)
//     Uint64 lastTime = SDL_GetTicks();  // Lấy thời điểm bắt đầu

//     // 4. Vòng lặp chính (Main Loop)
//     while (running) {
//         // Xử lý sự kiện
//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_EVENT_QUIT) {
//                 running = false;
//             }
//         }

//         // --- Bắt đầu phần xoay thời gian thực (Runtime) ---

//         // Tính delta time (khoảng thời gian giữa 2 khung hình - giây)
//         Uint64 currentTime = SDL_GetTicks();
//         float deltaTime = (currentTime - lastTime) / 1000.0f; // Chuyển sang giây
//         lastTime = currentTime;

//         // Cập nhật góc xoay dựa trên tốc độ và thời gian trôi qua
//         currentAngle += rotationSpeed * deltaTime;

//         // Giữ góc trong khoảng 0-360 độ (không bắt buộc nhưng tốt cho quản lý)
//         if (currentAngle >= 360.0f) {
//             currentAngle -= 360.0f;
//         }

//         // --- Bắt đầu phần Render ---

//         // Xóa màn hình bằng màu nền tối (R, G, B, A)
//         SDL_SetRenderDrawColorFloat(renderer, 0.1f, 0.1f, 0.15f, 1.0f);
//         SDL_RenderClear(renderer);

//         // Vẽ ảnh đã được xoay (Xoay quanh tâm ảnh, không lật)
//         // Các tham số: renderer, texture, source_rect (null = full), dest_rect, angle, center (null = center), flip
//         SDL_RenderTextureRotated(renderer, texture, nullptr, &dstRect, currentAngle, nullptr, SDL_FLIP_NONE);

//         // Cập nhật khung hình
//         SDL_RenderPresent(renderer);
//     }

//     // 5. Giải phóng tài nguyên
//     SDL_DestroyTexture(texture);
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
// }