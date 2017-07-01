
#ifndef __EquatorialInertial_H__
#define __EquatorialInertial_H__

#include "BaseSRF.hpp"
#include "Coord.hpp"
#include "Exception.hpp"

namespace srm
{
/** SRF_EquatorialInertial class declaration.
    SRFs are allocated by the API, and when no longer needed they should be
    released by calling the release() method.
    @author David Shen
    @see BaseSRF_3D
*/
class SRF_EquatorialInertial: public BaseSRF_3D
{
public:
   /** SRF_EquatorialInertial only constructor by ORM code
       @exception This method throws srm::Exception
    */
    static SRF_EquatorialInertial* create( SRM_ORM_Code orm, 
                                           SRM_RT_Code  rt );

   /** SRF_EquatorialInertial constructor by ORM parameters
       @exception This method throws srm::Exception
    */
    static SRF_EquatorialInertial* create( SRM_SRF_Parameters_Info srf_params )
    {
        return create( srf_params.value.srf_template.orm_code, srf_params.rt_code );
    }

   /** Returns a 3D coordinate object
    */
    Coord3D* createCoordinate3D(SRM_Long_Float coord_comp1,
                                SRM_Long_Float coord_comp2,
                                SRM_Long_Float coord_comp3 );
 
   /** Returns true if this SRF is of the given class type
    */
    virtual bool isA( SRF_ClassType type ) const;

   /** Returns the class type of this SRF instance
    */
    virtual SRF_ClassType getClassType() const
    {
        return BaseSRF::SRF_TYP_EI;
    }

   /** Returns true if the SRF parameters are equal
       @note This method is deprecated.  Use the equality operator instead.
    */
    bool isEqual( const SRF_EquatorialInertial &srf ) const;

   /** The equality operator
       @note This operator returns true if the SRFs have identical parameter values.
    */
    bool operator==( const SRF_EquatorialInertial &rhs ) const;

   /** Returns a copy of this SRF object
       @exception This method throws srm::Exception
    */
    SRF_EquatorialInertial* makeCopy() const;

   /** Returns char* of parameter names and their values
       @exception This method throws srm::Exception
    */
    const char* toString();

protected:
    SRF_EquatorialInertial( void *impl ) : BaseSRF_3D(impl) {} ///< No stack allocation
    SRF_EquatorialInertial &operator =( const SRF_EquatorialInertial & ) { return *this; } ///< No copy constructor
    virtual ~SRF_EquatorialInertial() {} ///< Use release()
};


inline bool SRF_EquatorialInertial::isA( SRF_ClassType type ) const
{
    if (type == BaseSRF::SRF_TYP_EI)
        return true;
    else
        return BaseSRF_3D::isA(type);
};


/// Shorthand version for SRF_EquatorialInertial
typedef SRF_EquatorialInertial SRF_EI;


/** A Coord3D for SRF_EquatorialInertial.
    @author David Shen
    @see SRF_EquatorialInertial
*/
class Coord3D_EquatorialInertial: public Coord3D
{
public:
   /** Constructor
    */
    Coord3D_EquatorialInertial( SRF_EquatorialInertial *srf, 
                                SRM_Long_Float right_ascension = 0.0,
                                SRM_Long_Float declination = 0.0,
                                SRM_Long_Float radius = 0.0 )
    : Coord3D(srf)
    {
        setComponentValues(right_ascension, declination, radius);
    }

   /** Copy constructor
    */
    Coord3D_EquatorialInertial( const Coord3D_EquatorialInertial &coord )
    : Coord3D(coord._srf)
    {
        setComponentValues( coord._values[0], coord._values[1], coord._values[2] );
    }

   /** Copies component values to the coordinate
       @note The coordinates must be associated with the same SRF instance.
       @note This method is deprecated.  Use the assignment operator.
       @exception This method throws srm::Exception
    */
    void copyTo( Coord3D_EquatorialInertial &coord ) const
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
    bool isEqual( const Coord3D_EquatorialInertial &coord ) const
    {
        return (_srf == coord._srf &&
                _values[0] == coord._values[0] &&
                _values[1] == coord._values[1] &&
                _values[2] == coord._values[2] );
    }

   /** Sets all coordinate component values
    */
    void setComponentValues( SRM_Long_Float right_ascension, SRM_Long_Float declination, SRM_Long_Float radius )
    {
        _values[0] = right_ascension;
        _values[1] = declination;
        _values[2] = radius;
    }

   /** Returns the right_ascension value
    */
    SRM_Long_Float get_right_ascension() const
    {
        return _values[0];
    }

   /** Returns the declination value
    */
    SRM_Long_Float get_declination() const
    {
        return _values[1];
    }

   /** Returns the radius value
    */
    SRM_Long_Float get_radius() const
    {
        return _values[2];
    }

   /** Sets the right_ascension value
    */
    void set_right_ascension( SRM_Long_Float value )
    {
        _values[0] = value;
    }

   /** Sets the declination value
    */
    void set_declination( SRM_Long_Float value )
    {
        _values[1] = value;
    }

   /** Sets the radius value
    */
    void set_radius( SRM_Long_Float value )
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
        return Coord::COORD_TYP_EI;
    }

   /** The equality operator
    */
    bool operator==( const Coord3D_EquatorialInertial &rhs ) const;

   /** Returns true if the coordinates are associated with SRFs with identical parameters.
       @note This method should be used to evaluate coordinate compatibility before
             calling the coordinate assignment operator to avoid raising runtime exception
             when operating on incompatible coordinates.
    */
    bool isCompatibleWith( const Coord3D_EquatorialInertial &rhs ) const
    {
        return ((*(SRF_EquatorialInertial*)(this->_srf)) == (*(SRF_EquatorialInertial*)(rhs._srf)));
    }

    /** The assignment operator
        @note This operator will check whether the coordinates are compatible.
        @exception This method throws srm::Exception
    */
    Coord3D_EquatorialInertial &operator= ( const Coord3D_EquatorialInertial &rhs )
    {
        if((*(SRF_EquatorialInertial*)(this->_srf)) == (*(SRF_EquatorialInertial*)(rhs._srf)))
        {
            _values[0] = rhs._values[0];
            _values[1] = rhs._values[1];
            _values[2] = rhs._values[2];
        }
        else
            throw Exception(SRM_STATCOD_INVALID_TARGET_COORDINATE,
                            "Coord3D_EquatorialInertial op=: incompatible rhs coordinate");

        return *this;
    }
};


inline bool Coord3D_EquatorialInertial::isA( Coord_ClassType type ) const
{
    if (type == Coord::COORD_TYP_EI)
        return true;
    else
        return Coord3D::isA(type);
};


/// Shorthand version for Coord3D_EquatorialInertial
typedef Coord3D_EquatorialInertial Coord3D_EI;

} // namespace srm

#endif // _EquatorialInertial_h
