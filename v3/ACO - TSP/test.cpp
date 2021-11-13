#include <iostream>
#include <random>
int main() {
    /* 隨機設備 */
    std::random_device rd;

    /* 亂數產生器 */
    std::default_random_engine generator(rd());

    /* 亂數的機率分布 */
    std::uniform_real_distribution<float> unif(0.0, 1.0);

    /* 產生亂數 */
    float x = unif(generator);

    std::cout << "x = " << x << std::endl;
    return 0;
}