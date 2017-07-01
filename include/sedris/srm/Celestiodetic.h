
#ifndef __Celestiodetic_H__
#define __Celestiodetic_H__

#include "BaseSRF.h"
#include "Coord.h"
#include "Exception.h"

namespace srm
{
/** SRF_Celestiodetic class declaration.
    SRFs are allocated by the API, and when no longer needed they should be
    released by calling the release() method.
    @author David Shen
    @see BaseSRF_WithEllipsoidalHeight
 */
class SRF_Celestiodetic: public BaseSRF_WithEllipsoidalHeight
{
public:
   /** SRF_Celestiodetic only constructor by ORM code
       @exception This method throws srm::Exception
    */
    static SRF_Celestiodetic* create( SRM_ORM_Code orm,
                                      SRM_RT_Code  rt );

   /** SRF_Celestiodetic constructor by ORM parameters
       @exception This method throws srm::Exception
    */
    static SRF_Celestiodetic* create( SRM_SRF_Parameters_Info srf_params )
    {
        return create( srf_params.value.srf_template.orm_code, srf_params.rt_code );
    }

   /** Returns a 3D coordinate object
    */
    Coord3D* createCoordinate3D(SRM_Long_Float coord_comp1,
                                SRM_Long_Float coord_comp2,
                                SRM_Long_Float coord_comp3 );

   /** Returns a surface coordinate object
    */
    CoordSurf* createSurfaceCoordinate(SRM_Long_Float coord_surf_comp1,
                                       SRM_Long_Float coord_surf_comp2 );

   /** Returns true if this SRF is of the given class type
    */
    virtual bool isA( SRF_ClassType type ) const;

   /** Returns the class type of this SRF instance
    */
    virtual SRF_ClassType getClassType() const
    {
        return BaseSRF::SRF_TYP_CD;
    }

   /** Returns true if the SRFs have identical parameter values.
       @note This method is deprecated.  Use the equality operator instead.
    */
    bool isEqual( const SRF_Celestiodetic &srf ) const;

   /** The equality operator
       @note This operator returns true if the SRFs have identical parameter values.
    */
    bool operator==( const SRF_Celestiodetic &rhs ) const;

   /** Returns a copy of this SRF object
       @exception This method throws srm::Exception
    */
    SRF_Celestiodetic* makeCopy() const;

   /** Changes a coordinate's values to this SRF (optimized implementation).
       @note The destination coordinate must have been created using this SRF.
       @param src_coord in: the source coordinate in some other SRF
       @param des_coord in/out: the destination coordinate in this SRF
       @return validity code for the destination coordinate
       @exception This method throws srm::Exception
    */
    virtual SRM_Coordinate_Valid_Region changeCoordinate3DSRF(const Coord3D &src_coord,
                                                                    Coord3D &des_coord );

   /** Returns char* of parameter names and their values
       @exception This method throws srm::Exception
    */
    const char* toString();

protected:
    friend class BaseSRF;
    SRF_Celestiodetic( void *impl ); ///< No stack allocation
    SRF_Celestiodetic &operator =( const SRF_Celestiodetic & ) { return *this; } ///< No copy constructor
    virtual ~SRF_Celestiodetic(); ///< Use release()
};


inline bool SRF_Celestiodetic::isA( SRF_ClassType type ) const
{
    if (type == BaseSRF::SRF_TYP_CD)
        return true;
    else
        return BaseSRF_WithEllipsoidalHeight::isA(type);
};


/// Shorthand version for SRF_Celestiodetic
typedef SRF_Celestiodetic SRF_CD;


/** A Coord3D for SRF_Celestiodetic.
    @author David Shen
    @see SRF_Celestiodetic
 */
class Coord3D_Celestiodetic: public Coord3D
{
public:
   /** Constructor
    */
    Coord3D_Celestiodetic(SRF_Celestiodetic *srf,
                          SRM_Long_Float longitude = 0.0,
                          SRM_Long_Float latitude = 0.0,
                          SRM_Long_Float ellipsoidal_height = 0.0 )
    : Coord3D(srf)
    {
        setComponentValues(longitude, latitude, ellipsoidal_height);
    }

   /** Copy constructor
    */
    Coord3D_Celestiodetic( const Coord3D_Celestiodetic &coord )
    : Coord3D(coord._srf)
    {
        setComponentValues( coord._values[0], coord._values[1], coord._values[2] );
    }

   /** Copies component values to the coordinate
       @note The coordinates must be associated with the same SRF instance.
       @note This method is deprecated.  Use the assignment operator.
       @exception This method throws srm::Exception
    */
    void copyTo( Coord3D_Celestiodetic &coord ) const
    {
        if (coord._srf != _srf)
            throw Exception( SRM_STATCOD_INVALID_SOURCE_COORDINATE, "copyTo: Coordinate associated with a difference SRF" );

        coord._values[0] = _values[0];
        coord._values[1] = _values[1];
        coord._values[2] = _values[2];
    }

   /** Returns true if the coordinate component values are identical
       @note This method is deprecated.  Use the equality operator instead.
    */
    bool isEqual( const Coord3D_Celestiodetic &coord ) const
    {
        return (_srf == coord._srf &&
                _values[0] == coord._values[0] &&
                _values[1] == coord._values[1] &&
                _values[2] == coord._values[2] );
    }

   /** Sets all coordinate component values
    */
    void setComponentValues( SRM_Long_Float longitude, SRM_Long_Float latitude, SRM_Long_Float ellipsoidal_height )
    {
        _values[0] = longitude;
        _values[1] = latitude;
        _values[2] = ellipsoidal_height;
    }

   /** Returns the longitude value
    */
    SRM_Long_Float get_longitude() const
    {
        return _values[0];
    }

   /** Returns the latitude value
    */
    SRM_Long_Float get_latitude() const
    {
        return _values[1];
    }

   /** Returns the ellipsoidal_height value
    */
    SRM_Long_Float get_ellipsoidal_height() const
    {
        return _values[2];
    }

   /** Sets the longitude value
    */
    void set_longitude( SRM_Long_Float value )
    {
        _values[0] = value;
    }

   /** Sets the latitude value
    */
    void set_latitude( SRM_Long_Float value )
    {
        _values[1] = value;
    }

   /** Sets the ellipsoidal_height value
    */
    void set_ellipsoidal_height( SRM_Long_Float value )
    {
        _values[2] = value;
    }

   /** Returns true if this coordinate is of the given class type
    */
    virtual bool isA( Coord_ClassType type ) const;

   /** Returns true if this SRF is of the given class type
    */
    virtual Coord_ClassType getClassType() const
    {
        return Coord::COORD_TYP_CD;
    }

   /** The equality operator
    */
    bool operator==( const Coord3D_Celestiodetic &rhs ) const;

   /** Returns true if the coordinates are associated with SRFs with identical parameters.
        @note This method should be used to evaluate coordinate compatibility before
              calling the coordinate assignment operator to avoid raising runtime exception
              when operating on incompatible coordinates.
    */
    bool isCompatibleWith( const Coord3D_Celestiodetic &rhs ) const
    {
        return ((*(SRF_Celestiodetic*)(this->_srf)) == (*(SRF_Celestiodetic*)(rhs._srf)));
    }

    /** The assignment operator
        @note This operator will check whether the coordinates are compatible.
        @exception This method throws srm::Exception
    */
    Coord3D_Celestiodetic &operator= ( const Coord3D_Celestiodetic &rhs )
    {
        if((*(SRF_Celestiodetic*)(this->_srf)) == (*(SRF_Celestiodetic*)(rhs._srf)))
        {
            _values[0] = rhs._values[0];
            _values[1] = rhs._values[1];
            _values[2] = rhs._values[2];
        }
        else
            throw Exception(SRM_STATCOD_INVALID_TARGET_COORDINATE,
                            "Coord3D_Celestiodetic op=: incompatible rhs coordinate");

        return *this;
    }
};


inline bool Coord3D_Celestiodetic::isA( Coord_ClassType type ) const
{
    if (type == Coord::COORD_TYP_CD)
        return true;
    else
        return Coord3D::isA(type);
};


/// Shorthand version for Coord3D_Celestiodetic
typedef Coord3D_Celestiodetic Coord3D_CD;


/** A CoordSurf for SRF_Celestiodetic.
    @author David Shen
    @see SRF_Celestiodetic
 */
class CoordSurf_Celestiodetic: public CoordSurf
{
public:
   /** Constructor
    */
    CoordSurf_Celestiodetic(SRF_Celestiodetic *srf,
                            SRM_Long_Float longitude = 0.0,
                            SRM_Long_Float latitude = 0.0 )
    : CoordSurf(srf)
    {
        setComponentValues(longitude, latitude);
    }

   /** Copy constructor
    */
    CoordSurf_Celestiodetic( const CoordSurf_Celestiodetic &coord )
    : CoordSurf(coord._srf)
    {
        setComponentValues( coord._values[0], coord._values[1] );
    }

   /** Copies component values to the coordinate
       @note The coordinates must be associated with the same SRF instance.
       @note This method is deprecated.  Use the assignment operator.
       @exception This method throws srm::Exception
    */
    void copyTo( CoordSurf_Celestiodetic &coord ) const
    {
        if (coord._srf != _srf)
            throw Exception( SRM_STATCOD_INVALID_SOURCE_COORDINATE, "copyTo: Coordinate associated with a difference SRF" );

        coord._values[0] = _values[0];
        coord._values[1] = _values[1];
    }

   /** Returns true if the coordinate component values are identical
       @note This method is deprecated.  Use the equality operator instead.
    */
    bool isEqual( const CoordSurf_Celestiodetic &coord ) const
    {
        return (_srf == coord._srf &&
                _values[0] == coord._values[0] &&
                _values[1] == coord._values[1] );
    }

   /** Sets all coordinate component values
    */
    void setComponentValues( SRM_Long_Float longitude, SRM_Long_Float latitude )
    {
        _values[0] = longitude;
        _values[1] = latitude;
    }

   /** Returns the longitude value
    */
    SRM_Long_Float get_longitude() const
    {
        return _values[0];
    }

   /** Returns the latitude value
    */
    SRM_Long_Float get_latitude() const
    {
        return _values[1];
    }

   /** Sets the longitude value
    */
    void set_longitude( SRM_Long_Float value )
    {
        _values[0] = value;
    }

   /** Sets the latitude value
    */
    void set_latitude( SRM_Long_Float value )
    {
        _values[1] = value;
    }

   /** Returns true if this coordinate is of the given class type
    */
    virtual bool isA( Coord_ClassType type ) const;

   /** Returns true if this SRF is of the given class type
    */
    virtual Coord_ClassType getClassType() const
    {
        return Coord::COORD_TYP_SURF_CD;
    }

   /** The equality operator
    */
    bool operator==(const CoordSurf_Celestiodetic &rhs) const;

   /** Returns true if the coordinates are associated with SRFs with identical parameters.
       @note This method should be used to evaluate coordinate compatibility before
             calling the coordinate assignment operator to avoid raising runtime exception
             when operating on incompatible coordinates.
    */
    bool isCompatibleWith( const CoordSurf_Celestiodetic &rhs ) const
    {
        return ((*(SRF_Celestiodetic*)(this->_srf)) == (*(SRF_Celestiodetic*)(rhs._srf)));
    }

   /** The assignment operator
       @note This operator will check whether the coordinates are compatible.
       @exception This method throws srm::Exception
    */
    CoordSurf_Celestiodetic &operator= ( const CoordSurf_Celestiodetic &rhs )
    {
        if((*(SRF_Celestiodetic*)(this->_srf)) == (*(SRF_Celestiodetic*)(rhs._srf)))
        {
            _values[0] = rhs._values[0];
            _values[1] = rhs._values[1];
        }
        else
            throw Exception(SRM_STATCOD_INVALID_TARGET_COORDINATE,
                          "CoordSurf_Celestiodetic op=: incompatible rhs coordinate");

        return *this;
    }
};


inline bool CoordSurf_Celestiodetic::isA( Coord_ClassType type ) const
{
    if (type == Coord::COORD_TYP_SURF_CD)
        return true;
    else
        return CoordSurf::isA(type);
};


/// Shorthand version for CoordSurf_Celestiodetic
typedef CoordSurf_Celestiodetic CoordSurf_CD;

} // namespace srm

#endif // _Celestiodetic_h
