#include <cassert>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define F        ThreeValuedLogic::False
#define T        ThreeValuedLogic::True
#define U        ThreeValuedLogic::Unknown

# define INIT \
    ThreeValuedLogic F = ThreeValuedLogic(Type::FALSE); \
    ThreeValuedLogic T = ThreeValuedLogic(Type::TRUE); \
    ThreeValuedLogic U = ThreeValuedLogic(Type::UNKNOWN);

struct ThreeValuedLogic {
public:
    static ThreeValuedLogic False;
    static ThreeValuedLogic True;
    static ThreeValuedLogic Unknown;

    ThreeValuedLogic operator| (const ThreeValuedLogic& other) {
        return ThreeValuedLogic(MAX(type, other.type));
    }

    ThreeValuedLogic operator& (const ThreeValuedLogic& other) {
        return ThreeValuedLogic(MIN(type, other.type));
    }

    bool operator== (const ThreeValuedLogic& other) {
        return type == other.type;
    }

    bool operator!= (const ThreeValuedLogic& other) {
        return type != other.type;
    }

    ThreeValuedLogic operator! () {
        return ThreeValuedLogic((Type) ((-1) * (short) type));
    }

    short to_short() {
        return (short) type;
    }

private:
    enum Type : short {
        FALSE = -1,
        UNKNOWN = 0,
        TRUE = 1,
    };

    ThreeValuedLogic(Type _type) {
        type = _type;
    }

    Type type;
};

INIT

int main(void) {
    assert((F | T) == T);
    assert((F | U) == U);
    assert((T | U) == T);
    assert((F | F) == F);
    assert((T | T) == T);
    assert((U | U) == U);

    assert((F & T) == F);
    assert((F & U) == F);
    assert((T & U) == U);
    assert((F & F) == F);
    assert((T & T) == T);
    assert((U & U) == U);

    assert( !F == T);
    assert( !T == F);
    assert( !U == U);

    assert( !F != F);
    assert( !T != U);

    return 0;
}
