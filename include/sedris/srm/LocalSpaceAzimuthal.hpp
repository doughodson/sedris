
#ifndef __LocalSpaceAzimuthal_H__
#define __LocalSpaceAzimuthal_H__

#include "BaseSRF.hpp"
#include "Coord.hpp"
#include "Exception.hpp"

namespace srm
{
/** SRF_LocalSpaceAzimuthal class declaration.
    SRFs are allocated by the API, and when no longer needed they should be
    released by calling the release() method.
    @author David Shen
    @see BaseSRF_2D
 */
class SRF_LocalSpaceAzimuthal: public BaseSRF_2D
{
public:
   /** SRF_LocalSpaceAzimuthal only constructor by ORM code
       @exception This method throws srm::Exception
    */
    static SRF_LocalSpaceAzimuthal* create( SRM_ORM_Code orm,
                                            SRM_RT_Code  rt );

   /** SRF_LocalSpaceAzimuthal constructor by ORM parameters
       @exception This method throws srm::Exception
    */
    static SRF_LocalSpaceAzimuthal* create( SRM_SRF_Parameters_Info srf_params )
    {
        return create( srf_params.value.srf_template.orm_code, srf_params.rt_code );
    }

   /** Returns a 2D coordinate object
    */
    Coord2D* createCoordinate2D(SRM_Long_Float coord_comp1,
                                SRM_Long_Float coord_comp2 );

   /** Returns true if this SRF is of the given class type
    */
    virtual bool isA( SRF_ClassType type ) const;

   /** Returns the class type of this SRF instance
    */
    virtual SRF_ClassType getClassType() const
    {
        return BaseSRF::SRF_TYP_LSA;
    }

   /** Returns true if the SRF parameters are equal
       @note This method is deprecated.  Use the equality operator instead.
    */
    bool isEqual( const SRF_LocalSpaceAzimuthal &srf ) const;

   /** The equality operator
       @note This operator returns true if the SRFs have identical parameter values.
    */
    bool operator==( const SRF_LocalSpaceAzimuthal &rhs ) const;

   /** Returns a copy of this SRF object
       @exception This method throws srm::Exception
    */
    SRF_LocalSpaceAzimuthal* makeCopy() const;

   /** Returns char* of parameter names and their values
       @exception This method throws srm::Exception
    */
    const char* toString();

protected:
    SRF_LocalSpaceAzimuthal( void *impl ) : BaseSRF_2D(impl) {} ///< No stack allocation
    SRF_LocalSpaceAzimuthal &operator =( const SRF_LocalSpaceAzimuthal & ) { return *this; } ///< No copy constructor
    virtual ~SRF_LocalSpaceAzimuthal() {} ///< Use release()
};


inline bool SRF_LocalSpaceAzimuthal::isA( SRF_ClassType type ) const
{
    if (type == BaseSRF::SRF_TYP_LSA)
        return true;
    else
        return BaseSRF_2D::isA(type);
};


/// Shorthand version for SRF_LocalSpaceAzimuthal
typedef SRF_LocalSpaceAzimuthal SRF_LSA;


/** A Coord2D for SRF_LocalSpaceAzimuthal.
    @author David Shen
    @see SRF_LocalSpaceAzimuthal
 */
class Coord2D_LocalSpaceAzimuthal: public Coord2D
{
public:
   /** Constructor
    */
    Coord2D_LocalSpaceAzimuthal( SRF_LocalSpaceAzimuthal *srf,
                                 SRM_Long_Float azimuth = 0.0,
                                 SRM_Long_Float radius = 0.0 )
    : Coord2D(srf)
    {
        setComponentValues(azimuth, radius);
    }

   /** Copy constructor
    */
    Coord2D_LocalSpaceAzimuthal( const Coord2D_LocalSpaceAzimuthal &coord )
    : Coord2D(coord._srf)
    {
        setComponentValues( coord._values[0], coord._values[1] );
    }

   /** Copies component values to the coordinate
       @note The coordinates must be associated with the same SRF instance.
       @note This method is deprecated.  Use the assignment operator.
       @exception This method throws srm::Exception
    */
    void copyTo( Coord2D_LocalSpaceAzimuthal &coord ) const
    {
        if (coord._srf != _srf)
            throw Exception( SRM_STATCOD_INVALID_SOURCE_COORDINATE, "copyTo: Coordinate associated with a difference SRF" );

        coord._values[0] = _values[0];
        coord._values[1] = _values[1];
    }

   /** Returns true if the coordinate component values are identical
       @note This method is deprecated.  Use the equality operator.
    */
    bool isEqual( const Coord2D_LocalSpaceAzimuthal &coord ) const
    {
        return (_srf == coord._srf &&
                _values[0] == coord._values[0] &&
                _values[1] == coord._values[1] );
    }

   /** Sets all coordinate component values
    */
    void setComponentValues( SRM_Long_Float azimuth, SRM_Long_Float radius )
    {
        _values[0] = azimuth;
        _values[1] = radius;
    }

   /** Returns the azimuth value
    */
    SRM_Long_Float get_azimuth() const
    {
        return _values[0];
    }

   /** Returns the radius value
    */
    SRM_Long_Float get_radius() const
    {
        return _values[1];
    }

   /** Sets the azimuth value
    */
    void set_azimuth( SRM_Long_Float value )
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
        return Coord::COORD_TYP_LSA;
    }

   /** The equality operator
    */
    bool operator==( const Coord2D_LocalSpaceAzimuthal &rhs ) const;

   /** Returns true if the coordinates are associated with SRFs with identical parameters.
       @note This method should be used to evaluate coordinate compatibility before
             calling the coordinate assignment operator to avoid raising runtime exception
             when operating on incompatible coordinates.
    */
    bool isCompatibleWith( const Coord2D_LocalSpaceAzimuthal &rhs ) const
    {
        return ((*(SRF_LocalSpaceAzimuthal*)(this->_srf)) == (*(SRF_LocalSpaceAzimuthal*)(rhs._srf)));
    }

   /** The assignment operator
       @note This operator will check whether the coordinates are compatible.
       @exception This method throws srm::Exception
    */
    Coord2D_LocalSpaceAzimuthal &operator= ( const Coord2D_LocalSpaceAzimuthal &rhs )
    {
        if((*(SRF_LocalSpaceAzimuthal*)(this->_srf)) == (*(SRF_LocalSpaceAzimuthal*)(rhs._srf)))
        {
            _values[0] = rhs._values[0];
            _values[1] = rhs._values[1];
        }
        else
            throw Exception(SRM_STATCOD_INVALID_TARGET_COORDINATE,
                            "SRF_LocalSpaceAzimuthal op=: incompatible rhs coordinate");

        return *this;
    }
};


inline bool Coord2D_LocalSpaceAzimuthal::isA( Coord_ClassType type ) const
{
    if (type == Coord::COORD_TYP_LSA)
        return true;
    else
        return Coord2D::isA(type);
};


/// Shorthand version for Coord2D_LocalSpaceAzimuthal
typedef Coord2D_LocalSpaceAzimuthal Coord2D_LSA;

} // namespace srm

#endif // _LocalSpaceAzimuthal_h
