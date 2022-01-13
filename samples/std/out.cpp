#include <iostream>
#include <vector>

class c0_Vector;


class c0_Vector {
public:
    int cv0_size_;
    int cv1_cap;
    int* cv2_elems;

public:
    int m0_size() {
        return cv0_size_;
    }

    void m1_add(int p0_e) {
        if ((cv0_size_ == cv1_cap)) {
            resize();
        }
        (cv0_size_ = (cv0_size_ + 1));
        (cv2_elems[cv0_size_] = p0_e);
    }

    void m2_resize() {
        int lv0_tmp;
        int lv1_i;

        (lv0_tmp = new int);
        (cv1_cap = (2 * cv0_size_));
        (lv1_i = 0);
        while ((lv1_i < cv0_size_)) {
            (lv0_tmp[lv1_i] = cv2_elems[lv1_i]);
            (lv1_i = (lv1_i + 1));
        }
        (cv2_elems = lv0_tmp);
    }
};

int main(int argc, char** argv) {
    return 0;
}
