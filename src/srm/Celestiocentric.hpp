
#ifndef __Celestiocentric_H__
#define __Celestiocentric_H__

#include "BaseSRF.hpp"
#include "Coord.hpp"
#include "Exception.hpp"

namespace srm
{
/** SRF_Celestiocentric class declaration.
    SRFs are allocated by the API, and when no longer needed they should be
    released by calling the release() method.
    @author David Shen
    @see BaseSRF_3D
 */
class SRF_Celestiocentric: public BaseSRF_3D
{
public:
   /** SRF_Celestiocentric only constructor by ORM code
       @exception This method throws srm::Exception
    */
    static SRF_Celestiocentric* create( SRM_ORM_Code orm,
                                        SRM_RT_Code  rt );

   /** SRF_Celestiocentric constructor by ORM parameters
       @exception This method throws srm::Exception
    */
    static SRF_Celestiocentric* create( SRM_SRF_Parameters_Info srf_params )
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
        return BaseSRF::SRF_TYP_CC;
    }

    /** Returns true if the SRF parameters are equal
        @note This method is deprecated.  Use the equality operator instead.
    */
    bool isEqual( const SRF_Celestiocentric &srf ) const;

    /** The equality operator
        @note This operator returns true if the SRFs have identical parameter values.
    */
    bool operator==( const SRF_Celestiocentric &rhs ) const;

    /** Returns a copy of this SRF object
        @exception This method throws srm::Exception
    */
    SRF_Celestiocentric* makeCopy() const;

    /** Changes a coordinate's values to this SRF (optimized implementation).
        @note The destination coordinate must have been created using this SRF.
        @param src_coord in: the source coordinate in some other SRF
        @param des_coord in/out: the destination coordinate in this SRF
        @return validity code for the destination coordinate
        @exception This method throws srm::Exception
    */
    virtual SRM_Coordinate_Valid_Region changeCoordinate3DSRF( const Coord3D &src_coord,
                                                               Coord3D &des_coord );

   /** Returns char* of parameter names and their values
       @exception This method throws srm::Exception
    */
    const char* toString();

protected:
    friend class BaseSRF;
    SRF_Celestiocentric( void *impl ); ///< No stack allocation
    SRF_Celestiocentric &operator =( const SRF_Celestiocentric & ) { return *this; } ///< No copy constructor
    virtual ~SRF_Celestiocentric(); ///< Use release()
};


inline bool SRF_Celestiocentric::isA( SRF_ClassType type ) const
{
    if (type == BaseSRF::SRF_TYP_CC)
        return true;
    else
        return BaseSRF_3D::isA(type);
};


/// Shorthand version for SRF_Celestiocentric
typedef SRF_Celestiocentric SRF_CC;


/** A Coord3D for SRF_Celestiocentric.
    @author David Shen
    @see SRF_Celestiocentric
 */
class Coord3D_Celestiocentric: public Coord3D
{
public:
   /** Constructor
    */
    Coord3D_Celestiocentric( SRF_Celestiocentric *srf,
                             SRM_Long_Float u = 0.0,
                             SRM_Long_Float v = 0.0,
                             SRM_Long_Float w = 0.0 )
    : Coord3D(srf)
    {
        setComponentValues(u, v, w);
    }

   /** Copy constructor
    */
    Coord3D_Celestiocentric( const Coord3D_Celestiocentric &coord )
    : Coord3D(coord._srf)
    {
        setComponentValues( coord._values[0], coord._values[1], coord._values[2] );
    }

   /** Copies component values to the coordinate
       @note The coordinates must be associated with the same SRF instance.
       @note This method is deprecated.  Use the assignment operator.
       @exception This method throws srm::Exception
    */
    void copyTo( Coord3D_Celestiocentric &coord ) const
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
    bool isEqual( const Coord3D_Celestiocentric &coord ) const
    {
        return (_srf == coord._srf &&
                _values[0] == coord._values[0] &&
                _values[1] == coord._values[1] &&
                _values[2] == coord._values[2] );
    }

   /** Sets all coordinate component values
    */
    void setComponentValues( SRM_Long_Float u, SRM_Long_Float v, SRM_Long_Float w )
    {
        _values[0] = u;
        _values[1] = v;
        _values[2] = w;
    }

   /** Returns the u value
    */
    SRM_Long_Float get_u() const
    {
        return _values[0];
    }

   /** Returns the v value
    */
    SRM_Long_Float get_v() const
    {
        return _values[1];
    }

   /** Returns the w value
    */
    SRM_Long_Float get_w() const
    {
        return _values[2];
    }

   /** Sets the u value
    */
    void set_u( SRM_Long_Float value )
    {
        _values[0] = value;
    }

   /** Sets the v value
    */
    void set_v( SRM_Long_Float value )
    {
        _values[1] = value;
    }

   /** Sets the w value
    */
    void set_w( SRM_Long_Float value )
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
        return Coord::COORD_TYP_CC;
    }

   /** The equality operator
    */
    bool operator==( const Coord3D_Celestiocentric &rhs ) const;

   /** Returns true if the coordinates are associated with SRFs with identical parameters.
       @note This method should be used to evaluate coordinate compatibility before
             calling the coordinate assignment operator to avoid raising runtime exception
             when operating on incompatible coordinates.
    */
    bool isCompatibleWith( const Coord3D_Celestiocentric &rhs ) const
    {
        return ((*(SRF_Celestiocentric*)(this->_srf)) == (*(SRF_Celestiocentric*)(rhs._srf)));
    }

    /** The assignment operator
        @note This operator will check whether the coordinates are compatible.
        @exception This method throws srm::Exception
    */
    Coord3D_Celestiocentric &operator= ( const Coord3D_Celestiocentric &rhs )
    {
        if((*(SRF_Celestiocentric*)(this->_srf)) == (*(SRF_Celestiocentric*)(rhs._srf)))
        {
            _values[0] = rhs._values[0];
            _values[1] = rhs._values[1];
            _values[2] = rhs._values[2];
        }
        else
            throw Exception(SRM_STATCOD_INVALID_TARGET_COORDINATE,
                            "Coord3D_Celestiocentric op=: incompatible rhs coordinate");

        return *this;
    }
};


inline bool Coord3D_Celestiocentric::isA( Coord_ClassType type ) const
{
    if (type == Coord::COORD_TYP_CC)
        return true;
    else
        return Coord3D::isA(type);
};


/// Shorthand version for Coord3D_Celestiocentric
typedef Coord3D_Celestiocentric Coord3D_CC;

} // namespace srm

#endif // _Celestiocentric_h
