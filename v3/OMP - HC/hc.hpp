#include <bitset>
#include <cstdio>
#include <random>
#include <vector>

using std::vector;

class hc {
    typedef vector<int> result;

  private:
    int NUM_X_DIM, NUM_MAX_ITER;

  public:
    hc(int x_dim, int max_iter) {
        NUM_X_DIM = x_dim;
        NUM_MAX_ITER = max_iter;
    }
    result run() {
        for (int ii = 0; ii < NUM_MAX_ITER; ii++) {
        }
    }
};