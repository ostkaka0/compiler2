#include <iostream>

 #include <ctime>
 #include <cstdio>

// Undefine for typeid checks
//#define CAST

class A
{
	virtual void LOL() { std::cout << " sdf\n"; }
}a;

class B : public A
{
		virtual void LOL() { std::cout << " sdf\n"; }
}b;

class C : public A
{
		virtual void LOL() { std::cout << " sdf\n"; }
}c;

class D : public B
{
		virtual void LOL() { std::cout << " sdf\n"; }
}d;

class E : public B
{
		virtual void LOL() { std::cout << " sdf\n"; }
}e;

class F : public C
{
		virtual void LOL() { std::cout << " sdf\n"; }
}f;

class G : public C
{
		virtual void LOL() { std::cout << " sdf\n"; }
}g;

class ZoomManager
{
public:
    void Subscribe(void *source)
    {
        mDelegate = new G();

        std::cout << "Subscribe\n";
		Fire(true);
    }

    void Fire(bool t1)
    {
        A *iDelegate;
        iDelegate = new E();

        int t = 0;
        clock_t start;

		start = clock();

        typedef F FireType;

        for ( int i = 0; i < 100000000; i++ ) {

#ifdef CAST
                if ( dynamic_cast< FireType* >( mDelegate ) )
#else
                // Change this line for comparisons .name() and & comparisons
                if ( typeid( *iDelegate ) == typeid( *mDelegate ) )
#endif
                {
                    t++;
                } else {
                    t--;
                }
        }

        //iEnd = clock();
        //printf("Clock ticks: %i,\n", iEnd - iStart );

        std::cout << typeid( *mDelegate ).name()<<"\n";

        double e = (std::clock() - start) / (double)CLOCKS_PER_SEC;
        std::cout << "Elasped: " << e;
    }

    template< class t1, class t2 >
    void Fire( t1 a1, t2 a2 )
    {
        std::cout << "Fire\n";
    }
	A *mDelegate;
};

class Scaler
{
public:
    Scaler( ZoomManager *aZoomManager ) :
        mZoomManager( aZoomManager ) { }

    void Sub()
    {
        mZoomManager->Subscribe(this);
    }

    void OnSizeChanged( int X  )
    {
        std::cout << "Yey!\n";        
    }
private:
    ZoomManager *mZoomManager;
};

int main(int argc, const char * argv[])
{
    ZoomManager *iZoomManager = new ZoomManager();

    Scaler iScaler( iZoomManager );
    iScaler.Sub();

    delete iZoomManager;

	std::cin.get();

    return 0;
}