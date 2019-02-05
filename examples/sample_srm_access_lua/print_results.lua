
PI = 3.14159265358979323846;
function to_degrees(rad) return rad*(180/PI) end

print("UTM (Zone N12) "
         .. "[ " .. utm_coord:get_easting()
         .. ", " .. utm_coord:get_easting()
         .. ", " .. utm_coord:get_northing()
         .. ", " .. utm_coord:get_ellipsoidal_height() .. " ]"
      )

print("  => CD "
        .. "[ " .. to_degrees(cd_coord:get_longitude())
        .. ", " .. to_degrees(cd_coord:get_latitude())
        .. ", " .. cd_coord:get_ellipsoidal_height() .. " ]"
     )

print("CD "
         .. "[ " .. to_degrees(cd_coord:get_longitude())
         .. ", " .. to_degrees(cd_coord:get_latitude())
         .. ", " .. cd_coord:get_ellipsoidal_height() .. " ]"
     )

print("  => CC "
       .. "[ " .. cc_coord:get_u() .. ", " .. cc_coord:get_v()
       .. ", " .. cc_coord:get_w() .. " ]"
     )
