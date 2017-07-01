
#ifndef __Exception_H__
#define __Exception_H__

#include "srm_types.h"

namespace srm
{

/** General exception handling class.
  This is the general exception class thrown from failed methods. An
exception typically contains an error code and a description string.
@author Warren Macchi (Accent Geographic)
*/
class Exception
{
public:

    enum {
        /// Maximum description string length in an Exception
        MAX_EXCEPTION_STR_LEN = 2000
    };

    /// Create exception with code only, no details description
    Exception( SRM_Status_Code code );
    /// Create exception with code and full description
    Exception( SRM_Status_Code code, const char *what );
    /// Create exception as a copy of another
    Exception( const Exception &other );
    /// Destructor
    virtual ~Exception() {}

    /// Copy exception data from another
    Exception &operator =( const Exception &other );

    /// Set the code and description information
    virtual void setCodeAndWhat( SRM_Status_Code code, const char *what )
    {
        int i=0;
        _code = code;
        while (what && *what && i < MAX_EXCEPTION_STR_LEN)
            _what[i] = *what, i++, what++;
        _what[i] = 0;
    }

    /// Returns the exception code value
    virtual SRM_Status_Code getCode() const { return _code; }
    /// Returns the exception description string
    virtual const char *getWhat() const { return _what; }

protected:

    SRM_Status_Code _code; ///< Exception error code
    char _what[MAX_EXCEPTION_STR_LEN+1]; ///< Exception error description
};


////////// Inlines

inline Exception::Exception( SRM_Status_Code code )
{
    setCodeAndWhat(code, "No details");
}


inline Exception::Exception( SRM_Status_Code code, const char *what )
{
    setCodeAndWhat(code, what);
}


inline Exception::Exception( const Exception &other )
{
    setCodeAndWhat(other.getCode(), other.getWhat());
}


inline Exception &Exception::operator =( const Exception &other )
{
    setCodeAndWhat(other.getCode(), other.getWhat());
    return *this;
}


} // namespace srm

#endif // _Exception_h
