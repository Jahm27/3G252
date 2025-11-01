#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>

#include <Dibujo.hpp>
#include <GestorDibujos.hpp>

using namespace ftxui;

static std::vector<std::u32string> GenLineaVertical(int alto, char32_t ch = U'|')
{
    std::vector<std::u32string> v;
    v.reserve(alto);
    for (int i = 0; i < alto; ++i)
        v.push_back(std::u32string(1, ch));
    return v;
}

static std::vector<std::u32string> GenLineaHorizontal(int ancho, char32_t ch = U'-')
{
    return {std::u32string(ancho, ch)};
}

static std::vector<std::u32string> GenHashMark()
{
    return {U"---"};
}

static std::vector<std::u32string> GenTexto(const std::u32string &s)
{
    return {s};
}

static std::vector<std::u32string> GenBalon()
{
    return {
        U" /\\ ",
        U"<==>",
        U" \\/ "};
}

int main()
{

    const int W = 80;
    const int H = 24;
    auto screen = Screen::Create(Dimension::Fixed(W), Dimension::Fixed(H));

    GestorDibujos gestor;

    const int x_left = 2;
    const int x_right = W - 3;

    gestor.Agregar(Dibujo(x_left, 1, GenLineaVertical(H - 2), ftxui::Color::Green1));
    gestor.Agregar(Dibujo(x_right, 1, GenLineaVertical(H - 2), ftxui::Color::Green1));

    for (int x = x_left + 8; x <= x_right - 8; x += 8)
    {
        gestor.Agregar(Dibujo(x, 1, GenLineaVertical(H - 2, U'|'), ftxui::Color::Green4));
    }

    const int y_hash_up = (int)(H * 0.42);
    const int y_hash_down = (int)(H * 0.58);
    for (int x = x_left + 8; x <= x_right - 8; x += 8)
    {

        gestor.Agregar(Dibujo(x - 1, y_hash_up, GenHashMark(), ftxui::Color::White));

        gestor.Agregar(Dibujo(x - 1, y_hash_down, GenHashMark(), ftxui::Color::White));
    }

    const int x_mid = (x_left + x_right) / 2;
    gestor.Agregar(Dibujo(x_mid, 1, GenLineaVertical(H - 2, U'|'), ftxui::Color::White));
    gestor.Agregar(Dibujo(x_mid + 1, 1, GenLineaVertical(H - 2, U'|'), ftxui::Color::White));

    gestor.Agregar(Dibujo(x_left - 1, 0, GenTexto(U"0"), ftxui::Color::White));
    gestor.Agregar(Dibujo(x_mid - 1, 0, GenTexto(U"50"), ftxui::Color::White));
    gestor.Agregar(Dibujo(x_right - 1, 0, GenTexto(U"0"), ftxui::Color::White));

    const int y_center = H / 2 - 1;
    Dibujo balon(x_left + 1, y_center, GenBalon(), ftxui::Color::RGB(210, 105, 30));
    gestor.Agregar(balon);
    const int idx_balon = (int)gestor.dibujos.size() - 1;

    const int fps_ms = 60;
    const int x_min = x_left + 1;
    const int x_max = x_right - 3;
    int x = x_min;
    int dir = +1;

    const bool ping_pong = false;

    for (;;)
    {

        if (ping_pong)
        {
            x += dir;
            if (x >= x_max || x <= x_min)
                dir *= -1;
        }
        else
        {
            x += 1;
            if (x > x_max)
                x = x_min;
        }
        gestor.dibujos[idx_balon].x = x;
        gestor.dibujos[idx_balon].y = y_center;

        screen.Clear();
        gestor.DibujarTodos(screen);

        std::cout << screen.ToString();
        std::cout << screen.ResetPosition();
        std::cout << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(fps_ms));
    }
    return 0;
}
