
#ifndef _M34_hpp_
#define _M34_hpp_

union M34 {
    
public:
    float raw [ 3 * 4 ];
    struct {
        float col [ 4 ];
    } row [ 3 ];
    struct {
        float x ; float M01 ; float M02 ; float M03 ;
        float y ; float M11 ; float M12 ; float M13 ;
        float z ; float M21 ; float M22 ; float M23 ;
    } x ;
    struct {
        float M00 ; float x ; float M02 ; float M03 ;
        float M10 ; float y ; float M12 ; float M13 ;
        float M20 ; float z ; float M22 ; float M23 ;
    } y ;
    struct {
        float M00 ; float M01 ; float x ; float M03 ;
        float M10 ; float M11 ; float y ; float M13 ;
        float M20 ; float M21 ; float z ; float M23 ;
    } z ;
    struct {
        float M00 ; float M01 ; float M02 ; float x ;
        float M10 ; float M11 ; float M12 ; float y ;
        float M20 ; float M21 ; float M22 ; float z ;
    } t ;

    M34();
    M34(
     float m00, float m01, float m02, float m03, 
     float m10, float m11, float m12, float m13, 
     float m20, float m21, float m22, float m23
    );

    void identity  ();
    void rotate_z  ( float r );
    void rotate_y  ( float r );
    void rotate_x  ( float r );
    void rotate    ( float x , float y , float z , float r );
    void translate ( float x , float y , float z );
    void multiply  ( M34 * other );
    void normalize ();
    void invert    ( M34 * dst , M34 * src );
    void to_opengl_matrix  ( float * glm );
    void to_opengl_heading ( float * glm );
    char *to_code( char *buf, int len );
    void m_dot_v( float *o, const float *i );
};


#endif

