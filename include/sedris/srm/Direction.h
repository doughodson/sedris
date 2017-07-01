
#ifndef __Direction_H__
#define __Direction_H__

#include "BaseSRF.h" ///< For SRF clone() and release() methods.
#include "Exception.h"

namespace srm
{
/** The Direction abstract contains a vector and a reference location.
@author Warren Macchi, David Shen
@see BaseSRF_3D
*/
class Direction
{
public:
    /** Returns the SRF this Direction belongs to.
        @exception This method throws srm::Exception
    */
    BaseSRF *getSRF() const
    {
        return _srf;
    }

    /** Gets the reference coordinate
        @exception This method throws srm::Exception
    */
    void getRefCoord( Coord3D &coord ) const;

    /** Gets the reference coordinate values
    */
    const SRM_Long_Float *getRefCoord() const;

    /** Gets the direction vector
    */
    void getDir( SRM_Vector_3D vec ) const;

    /** Gets the first component value of the vector
    */
    SRM_Long_Float getVectorComp1() const;

    /** Gets the second component value of the vector
    */
    SRM_Long_Float getVectorComp2() const;

    /** Gets the third component value of the vector
    */
    SRM_Long_Float getVectorComp3() const;

    /** Gets the nth component value of the vector
        @exception This method throws srm::Exception
        @note the index is [ 1, 2, 3 ]
    */
    SRM_Long_Float getVectorComp( SRM_Integer index ) const;

    /** Sets the direction vector values
    */
    void setVectorComp( const SRM_Long_Float comp1,
                        const SRM_Long_Float comp2,
                        const SRM_Long_Float comp3 );

    /** Sets the direction vector values
        @exception This method throws srm::Exception
        @note the index is [ 1, 2, 3 ]
    */
    void setVectorComp( const SRM_Integer    index,
                        const SRM_Long_Float comp );

    /** Sets the direction vector values
    */
    void setVector( const SRM_Vector_3D vec );

    /** Returns true if this has the same ref_coord and vector
    */
    bool isEqual( const Direction &dir ) const;

    /** Makes a shallow copy of this Direction object
    */
    Direction* makeCopy() const;

protected:
    friend class BaseSRF_3D;

    /** Constructor, requires an SRF, 3 reference coordinate values, and
        3 direction values.
        @exception This method throws srm::Exception
    */
    Direction(      BaseSRF       *srf,
              const SRM_Vector_3D  ref_coord,
              const SRM_Vector_3D  vec );

    /** Destructor, releases the SRF.
     */
    virtual ~Direction()
    {
        _srf->release();
    }

    Direction &operator =( const Direction & )
    { return *this; } ///< No copy constructor

    /** The SRF this Direction belongs to
     */
    BaseSRF *_srf;
    /** The reference coordinate values
     */
    SRM_Vector_3D _ref_coord;
    /** The direction values
     */
    SRM_Vector_3D _vec;
};

} // namespace srm

#endif // _Direction_h
