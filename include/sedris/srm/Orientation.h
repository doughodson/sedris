
#ifndef __Orientation_H__
#define __Orientation_H__

#include "Exception.h"

namespace srm
{
class BaseSRF;

/** The Orientation abstract contains a 3x3 matrix and a reference location.
    @author David Shen
    @see BaseSRF_3D
*/
class Orientation
{
public:
   /** Returns the SRF this Orientation belongs to.
    */
    BaseSRF *getSRF() const
    {
        return _srf;
    }

   /** Gets the reference coordinate
       @exception This method throws srm::Exception
    */
    void getRefCoord( Coord3D &coord ) const;

   /** Gets the orientation matrix
    */
    void getMatrix( SRM_Matrix_3x3 mat ) const;

   /** Gets the first Direction component of the Orientation
       @exception This method throws srm::Exception
    */
    void getDirectionComp1( Direction &dir ) const;

   /** Gets the second Direction component of the Orientation
       @exception This method throws srm::Exception
    */
    void getDirectionComp2( Direction &dir ) const;

   /** Gets the third Direction component of the Orientation
       @exception This method throws srm::Exception
    */
    void getDirectionComp3( Direction &dir ) const;

   /** Gets the nth Direction component of the Orientation
       @exception This method throws srm::Exception
       @note the index is [ 1, 2, 3 ]
    */
    void getDirectionComp( SRM_Integer index, Direction &dir ) const;

   /** Sets the Direction components of the Orientation
       @exception This method throws srm::Exception
    */
    void setDirectionComp( const Direction &dir1,
                           const Direction &dir2,
                           const Direction &dir3 );

   /** Sets the Direction components of the Orientation
       @note the index is [ 1, 2, 3 ]
       @exception This method throws srm::Exception
    */
    void setDirectionComp( const SRM_Integer index,
                           const Direction   &dir );

   /** Sets the orientation matrix values
    */
    void setMatrix( const SRM_Matrix_3x3 mat );

   /** Returns true if this has the same ref_coord and matrix
    */
    bool isEqual( const Orientation &ori ) const;

   /** The equality operator.
    */
    bool operator==(const Orientation & rhs) const;

   /** Makes a shallow copy of this Orientation object
    */
    Orientation* makeCopy() const;

protected:
    friend class BaseSRF_3D;

   /** Constructor, requires an SRF, 3 reference coordinate values, and a
       3x3 matrix.
    */
    Orientation( BaseSRF *srf,
                 const SRM_Vector_3D ref_coord,
                 const SRM_Matrix_3x3 matrix );

   /** Destructor, releases the SRF.
    */
    virtual ~Orientation();

    Orientation &operator =( const Orientation & ) { return *this; } ///< No copy constructor

   /** The SRF this Orientation belongs to
    */
    BaseSRF *_srf;
   /** The reference coordinate values
    */
    SRM_Vector_3D _ref_coord;
   /** The matrix values
    */
    SRM_Matrix_3x3 _mat;
};

} // namespace srm

#endif // _Orientation_h

