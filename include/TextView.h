#ifndef TEXT_VIEW
#define TEXT_VIEW
#include "View.h"

class TextView : public View {
    std::vector<std::vector<char>> _getBlockVector(char);
    
    public:
        TextView();
        ~TextView();
        void render();
};

#endif