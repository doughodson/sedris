
#ifndef __LocalTangentSpaceCylindrical_H__
#define __LocalTangentSpaceCylindrical_H__

#include "BaseSRF.h"
#include "Coord.h"
#include "Exception.h"

namespace srm
{
/** SRF_LocalTangentSpaceCylindrical class declaration.
    SRFs are allocated by the API, and when no longer needed they should be
    released by calling the release() method.
    @author David Shen
    @see BaseSRF_WithTangentPlaneSurface
 */
class SRF_LocalTangentSpaceCylindrical: public BaseSRF_WithTangentPlaneSurface
{
public:
   /** Constructor by SRF parameter structure
           @exception This method throws srm::Exception
    */
    static SRF_LocalTangentSpaceCylindrical* create(      SRM_ORM_Code orm,
                                                          SRM_RT_Code  rt,
                                                    const SRM_Local_Tangent_Parameters &params);

   /** Constructor by individual SRF parameters
       @exception This method throws srm::Exception
    */
    static SRF_LocalTangentSpaceCylindrical* create(
                                                    SRM_ORM_Code orm,
                                                    SRM_RT_Code  rt,
                                                    SRM_Long_Float geodetic_longitude,
                                                    SRM_Long_Float geodetic_latitude,
                                                    SRM_Long_Float azimuth,
                                                    SRM_Long_Float height_offset
                                                    );

   /** SRF_LocalTangentSpaceCylindrical constructor by SRF parameter structure
       @exception This method throws srm::Exception
    */
    static SRF_LocalTangentSpaceCylindrical* create( SRM_SRF_Parameters_Info srf_params )
    {
        return create( srf_params.value.srf_template.orm_code,
                       srf_params.rt_code,
                       srf_params.value.srf_template.parameters.ltsc_srf_parameters );
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

   /** Returns a reference to the SRF parameter structure
       @exception This method throws srm::Exception
    */
    const SRM_Local_Tangent_Parameters &getSRFParameters() const;

   /** Returns the geodetic_longitude SRF parameter value
        @exception This method throws srm::Exception
    */
    SRM_Long_Float get_geodetic_longitude() const;

   /** Returns the geodetic_latitude SRF parameter value
       @exception This method throws srm::Exception
    */
    SRM_Long_Float get_geodetic_latitude() const;

   /** Returns the azimuth SRF parameter value
       @exception This method throws srm::Exception
    */
    SRM_Long_Float get_azimuth() const;

   /** Returns the height_offset SRF parameter value
       @exception This method throws srm::Exception
    */
    SRM_Long_Float get_height_offset() const;

   /** Returns true if this SRF is of the given class type
    */
    virtual bool isA( SRF_ClassType type ) const;

   /** Returns the class type of this SRF instance
    */
    virtual SRF_ClassType getClassType() const
    {
        return BaseSRF::SRF_TYP_LTSC;
    }

   /** Returns true if the SRF parameters are equal
       @note This method is deprecated.  Use the equality operator instead.
    */
    bool isEqual( const SRF_LocalTangentSpaceCylindrical &srf ) const;

   /** The equality operator
       @note This operator returns true if the SRFs have identical parameter values.
    */
    bool operator==( const SRF_LocalTangentSpaceCylindrical &rhs ) const;

   /** Returns a copy of this SRF object
       @exception This method throws srm::Exception
    */
    SRF_LocalTangentSpaceCylindrical* makeCopy() const;

   /** Returns char* of parameter names and their values
       @exception This method throws srm::Exception
    */
    const char* toString();

protected:
    SRF_LocalTangentSpaceCylindrical( void *impl ) : BaseSRF_WithTangentPlaneSurface(impl) {} ///< No stack allocation
    SRF_LocalTangentSpaceCylindrical &operator =( const SRF_LocalTangentSpaceCylindrical & ) { return *this; } ///< No copy constructor
    virtual ~SRF_LocalTangentSpaceCylindrical() {} ///< Use release()
};


inline bool SRF_LocalTangentSpaceCylindrical::isA( SRF_ClassType type ) const
{
    if (type == BaseSRF::SRF_TYP_LTSC)
        return true;
    else
        return BaseSRF_WithTangentPlaneSurface::isA(type);
};


/// Shorthand version for SRF_LocalTangentSpaceCylindrical
typedef SRF_LocalTangentSpaceCylindrical SRF_LTSC;


/** A Coord3D for SRF_LocalTangentSpaceCylindrical.
    @author David Shen
    @see SRF_LocalTangentSpaceCylindrical
 */
class Coord3D_LocalTangentSpaceCylindrical: public Coord3D
{
public:
   /** Constructor
    */
    Coord3D_LocalTangentSpaceCylindrical(SRF_LocalTangentSpaceCylindrical *srf,
                                         SRM_Long_Float angle = 0.0,
                                         SRM_Long_Float radius = 0.0,
                                         SRM_Long_Float height = 0.0 )
    : Coord3D(srf)
    {
        setComponentValues(angle, radius, height);
    }

   /** Copy constructor
    */
    Coord3D_LocalTangentSpaceCylindrical( const Coord3D_LocalTangentSpaceCylindrical &coord )
    : Coord3D(coord._srf)
    {
        setComponentValues( coord._values[0], coord._values[1], coord._values[2] );
    }

   /** Copies component values to the coordinate
       @note The coordinates must be associated with the same SRF instance.
       @note This method is deprecated.  Use the assignment operator.
       @exception This method throws srm::Exception
    */
    void copyTo( Coord3D_LocalTangentSpaceCylindrical &coord ) const
    {
        if (coord._srf != _srf)
            throw Exception( SRM_STATCOD_INVALID_SOURCE_COORDINATE, "copyTo: Coordinate associated with a difference SRF" );

        coord._values[0] = _values[0];
        coord._values[1] = _values[1];
        coord._values[2] = _values[2];
    }

   /** Returns true if the coordinate component values are identical
       @note This method is deprecated.  Use the equality operator.
    */
    bool isEqual( const Coord3D_LocalTangentSpaceCylindrical &coord ) const
    {
        return (_srf == coord._srf &&
                _values[0] == coord._values[0] &&
                _values[1] == coord._values[1] &&
                _values[2] == coord._values[2] );
    }

   /** Sets all coordinate component values
    */
    void setComponentValues( SRM_Long_Float angle, SRM_Long_Float radius, SRM_Long_Float height )
    {
        _values[0] = angle;
        _values[1] = radius;
        _values[2] = height;
    }

   /** Returns the angle value
    */
    SRM_Long_Float get_angle() const
    {
        return _values[0];
    }

   /** Returns the radius value
    */
    SRM_Long_Float get_radius() const
    {
        return _values[1];
    }

   /** Returns the height value
    */
    SRM_Long_Float get_height() const
    {
        return _values[2];
    }

   /** Sets the angle value
    */
    void set_angle( SRM_Long_Float value )
    {
        _values[0] = value;
    }

   /** Sets the radius value
    */
    void set_radius( SRM_Long_Float value )
    {
        _values[1] = value;
    }

   /** Sets the height value
    */
    void set_height( SRM_Long_Float value )
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
        return Coord::COORD_TYP_LTSC;
    }

   /** The equality operator
    */
    bool operator==( const Coord3D_LocalTangentSpaceCylindrical &rhs ) const;

   /** Returns true if the coordinates are associated with SRFs with identical parameters.
       @note This method should be used to evaluate coordinate compatibility
             before calling the coordinate assignment operator to avoid raising
             runtime exception when operating on incompatible coordinates.
    */
    bool isCompatibleWith( const Coord3D_LocalTangentSpaceCylindrical &rhs ) const {
        return ((*(SRF_LocalTangentSpaceCylindrical*)(this->_srf)) == (*(SRF_LocalTangentSpaceCylindrical*)(rhs._srf)));
    }

   /** The assignment operator
       @note This operator will check whether the coordinates are compatible.
       @note Compatible coordinates are associated with SRFs with identical parameters.
       @exception This method throws srm::Exception
    */
    Coord3D_LocalTangentSpaceCylindrical &operator= ( const Coord3D_LocalTangentSpaceCylindrical &rhs )
    {
        if((*(SRF_LocalTangentSpaceCylindrical*)(this->_srf)) == (*(SRF_LocalTangentSpaceCylindrical*)(rhs._srf)))
        {
            _values[0] = rhs._values[0];
            _values[1] = rhs._values[1];
            _values[2] = rhs._values[2];
        }
        else
            throw Exception(SRM_STATCOD_INVALID_TARGET_COORDINATE,
                            "SRF_LocalTangentSpaceCylindrical op=: incompatible rhs coordinate");

        return *this;
    }
};


inline bool Coord3D_LocalTangentSpaceCylindrical::isA( Coord_ClassType type ) const
{
    if (type == Coord::COORD_TYP_LTSC)
        return true;
    else
        return Coord3D::isA(type);
};


/// Shorthand version for Coord3D_LocalTangentSpaceCylindrical
typedef Coord3D_LocalTangentSpaceCylindrical Coord3D_LTSC;


/** A CoordSurf for SRF_LocalTangentSpaceCylindrical.
    @author David Shen
    @see SRF_LocalTangentSpaceCylindrical
 */
class CoordSurf_LocalTangentSpaceCylindrical: public CoordSurf
{
public:
   /** Constructor
    */
    CoordSurf_LocalTangentSpaceCylindrical( SRF_LocalTangentSpaceCylindrical *srf,
                                            SRM_Long_Float angle = 0.0,
                                            SRM_Long_Float radius = 0.0 )
    : CoordSurf(srf)
    {
        setComponentValues(angle, radius);
    }

   /** Copy constructor
    */
    CoordSurf_LocalTangentSpaceCylindrical( const CoordSurf_LocalTangentSpaceCylindrical &coord )
    : CoordSurf(coord._srf)
    {
        setComponentValues( coord._values[0], coord._values[1] );
    }

   /** Copies component values to the coordinate
       @note The coordinates must be associated with the same SRF instance.
       @note This method is deprecated.  Use the assignment operator.
       @exception This method throws srm::Exception
    */
    void copyTo( CoordSurf_LocalTangentSpaceCylindrical &coord ) const
    {
        if (coord._srf != _srf)
            throw Exception( SRM_STATCOD_INVALID_SOURCE_COORDINATE, "copyTo: Coordinate associated with a difference SRF" );

        coord._values[0] = _values[0];
        coord._values[1] = _values[1];
    }

   /** Returns true if the coordinate component values are identical
       @note This method is deprecated.  Use the equality operator.
    */
    bool isEqual( const CoordSurf_LocalTangentSpaceCylindrical &coord ) const
    {
        return (_srf == coord._srf &&
                _values[0] == coord._values[0] &&
                _values[1] == coord._values[1] );
    }

   /** Sets all coordinate component values
    */
    void setComponentValues( SRM_Long_Float angle, SRM_Long_Float radius )
    {
        _values[0] = angle;
        _values[1] = radius;
    }

   /** Returns the angle value
    */
    SRM_Long_Float get_angle() const
    {
        return _values[0];
    }

   /** Returns the radius value
    */
    SRM_Long_Float get_radius() const
    {
        return _values[1];
    }

   /** Sets the angle value
    */
    void set_angle( SRM_Long_Float value )
    {
        _values[0] = value;
    }

   /** Sets the radius value
    */
    void set_radius( SRM_Long_Float value )
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
        return Coord::COORD_TYP_SURF_LTSC;
    }

   /** The equality operator
    */
    bool operator==( const CoordSurf_LocalTangentSpaceCylindrical &rhs ) const;

   /** Returns true if the coordinates are associated with SRFs with identical parameters.
       @note This method should be used to evaluate coordinate compatibility
             before calling the coordinate assignment operator to avoid raising
             runtime exception when operating on incompatible coordinates.
    */
    bool isCompatibleWith( const CoordSurf_LocalTangentSpaceCylindrical &rhs ) const
    {
        return ((*(SRF_LocalTangentSpaceCylindrical*)(this->_srf)) == (*(SRF_LocalTangentSpaceCylindrical*)(rhs._srf)));
    }

   /** The assignment operator
       @note This operator will check whether the coordinates are compatible.
       @note Compatible coordinates are associated with SRFs with identical parameters.
       @exception This method throws srm::Exception
    */
    CoordSurf_LocalTangentSpaceCylindrical &operator= ( const CoordSurf_LocalTangentSpaceCylindrical &rhs )
    {
        if((*(SRF_LocalTangentSpaceCylindrical*)(this->_srf)) == (*(SRF_LocalTangentSpaceCylindrical*)(rhs._srf)))
        {
            _values[0] = rhs._values[0];
            _values[1] = rhs._values[1];
        }
        else
            throw Exception(SRM_STATCOD_INVALID_TARGET_COORDINATE,
                            "CoordSurf_LocalTangentSpaceCylindrical op=: incompatible rhs coordinate");

        return *this;
    }
};


inline bool CoordSurf_LocalTangentSpaceCylindrical::isA( Coord_ClassType type ) const
{
    if (type == Coord::COORD_TYP_SURF_LTSC)
        return true;
    else
        return CoordSurf::isA(type);
};


/// Shorthand version for CoordSurf_LocalTangentSpaceCylindrical
typedef CoordSurf_LocalTangentSpaceCylindrical CoordSurf_LTSC;

} // namespace srm

#endif // _LocalTangentSpaceCylindrical_h
