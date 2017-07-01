
//
// DESCRIPTION:
//   Contains print functions for all SEDRIS types, and for
//   an object's fields.
//

#include <stdio.h>
#include <string.h>

#include "drm.h"

/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_Indent
 *
 *    Indent the number of spaces appropriate for the given level.
 *
 * PARAMETERS:
 *
 *   level -- 1/2 the number of spaces to indent
 *
 *   out_file_ptr -- output file to which we're printing
 *
 * RETURNS:
 *
 *   nothing
 *
 *-----------------------------------------------------------------------------
 */
static void
SE_Indent
(
    SE_Integer_Unsigned  level,
    FILE                *out_file_ptr
)
{
    SE_Integer_Unsigned i;

    for (i=1; i<level; i++)
        fprintf(out_file_ptr, "  ");
} /* end SE_Indent */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_LinkIndent
 *
 *    Indent the number of spaces appropriate for the given level.
 *
 * PARAMETERS:
 *
 *   level -- 1/2 the number of spaces to indent
 *
 *   out_file_ptr -- output file to which we're printing
 *
 * RETURNS:
 *
 *   nothing
 *
 *-----------------------------------------------------------------------------
 */
static void
SE_LinkIndent
(
    SE_Integer_Unsigned  level,
    FILE                *out_file_ptr
)
{
    SE_Integer_Unsigned i;

    for (i=2; i<level; i++)
        fprintf(out_file_ptr, "  ");
    fprintf(out_file_ptr, "| ");
} /* end SE_LinkIndent */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintDRMClassFields
 *
 *   Prints the object's fields.
 *
 * PARAMETERS:
 *
 *   field_ptr -- pointer to fields to print
 *
 *   name_ptr -- optional; name of field_ptr at the caller's level
 *
 *   level -- current indentation level. For each level, the output is
 *            indented 4 spaces; e.g., level = 0 means no indentation;
 *            level = 1 causes an indent of 4 spaces; level = 2 indents
 *            8 spaces, level = 3 indents 12 spaces, etc.
 *
 * RETURNS:
 *
 *   nothing
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintDRMClassFields
(
          SE_FIELDS_PTR        field_ptr,
    const char                *name_ptr,
          SE_Integer_Unsigned  level
)
{
    SRM_Integer_Unsigned  i;
    char                  name_buffer[1024];
    FILE                 *f_ptr = NULL, *orig_edcs_f_ptr = NULL,
                         *orig_srm_f_ptr = NULL;
    SRM_Status_Code       srm_stat_code;
    EDCS_Status_Code      edcs_stat_code;

    f_ptr           = SE_GetOutFilePtr();
    orig_edcs_f_ptr = EDCS_GetOutFilePtr();

    if ((srm_stat_code=SRM_SetOutFilePtr(f_ptr)) != SRM_STATCOD_SUCCESS)
    {
        fprintf(stderr, "SE_PrintDRMClassFields: "\
                "Can't set SRM out file pointer (%s), returning!\n",
                SRM_PrintStatusCode(srm_stat_code));
        return;
    }
    else if ((edcs_stat_code=EDCS_SetOutFilePtr(f_ptr)) !=
             EDCS_SC_SUCCESS)
    {
        fprintf(stderr, "SE_PrintDRMClassFields: "\
                "Can't set EDCS out file pointer (%s), returning!\n",
                EDCS_PrintStatusCode(edcs_stat_code));
        return;
    }
    switch (field_ptr->tag)
    {
        case SE_CLS_DRM_ABSOLUTE_TIME:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Absolute_Time.time_significance: %s\n",
                        name_ptr, SE_PrintTimeSignificance
                    (field_ptr->u.Absolute_Time.time_significance));
                sprintf(name_buffer,"%s->u.Absolute_Time.time_value",
                        name_ptr);
                SE_PrintTimeValue(&(field_ptr->u.Absolute_Time.time_value),
                  name_buffer, level);
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "time_significance: %s\n",
                        SE_PrintTimeSignificance
                    (field_ptr->u.Absolute_Time.time_significance));
                SE_PrintTimeValue(&(field_ptr->u.Absolute_Time.time_value),
                  "time_value", level);
            }
            break;

        case SE_CLS_DRM_ABSOLUTE_TIME_INTERVAL:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Absolute_Time_Interval.time_significance:"\
                        " %s\n",name_ptr, SE_PrintTimeSignificance
                    (field_ptr->u.Absolute_Time_Interval.time_significance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Absolute_Time_Interval.delta_days: %s\n",
                        name_ptr, SE_PrintInteger
                        (field_ptr->u.Absolute_Time_Interval.delta_days));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Absolute_Time_Interval.delta_hours:"\
                        " %s\n", name_ptr, SE_PrintByteUnsigned
                        (field_ptr->u.Absolute_Time_Interval.delta_hours));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Absolute_Time_Interval.delta_minutes:"\
                        " %s\n", name_ptr, SE_PrintByteUnsigned
                        (field_ptr->u.Absolute_Time_Interval.delta_minutes));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Absolute_Time_Interval.delta_seconds:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Absolute_Time_Interval.delta_seconds));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "time_significance: %s\n",
                        SE_PrintTimeSignificance
                    (field_ptr->u.Absolute_Time_Interval.time_significance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_days: %s\n", SE_PrintInteger
                        (field_ptr->u.Absolute_Time_Interval.delta_days));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_hours: %s\n", SE_PrintByteUnsigned
                        (field_ptr->u.Absolute_Time_Interval.delta_hours));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_minutes: %s\n", SE_PrintByteUnsigned
                        (field_ptr->u.Absolute_Time_Interval.delta_minutes));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_seconds: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Absolute_Time_Interval.delta_seconds));
            }
            break;

        case SE_CLS_DRM_AGGREGATE_FEATURE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Aggregate_Feature.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Aggregate_Feature.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Aggregate_Feature.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Aggregate_Feature.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Aggregate_Feature.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Aggregate_Feature.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_AGGREGATE_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Aggregate_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Aggregate_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Aggregate_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Aggregate_Geometry.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Aggregate_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Aggregate_Geometry.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_ALTERNATE_HIERARCHY_RELATED_FEATURES:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Alternate_Hierarchy_Related_Features.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Alternate_Hierarchy_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Alternate_Hierarchy_Related_Features.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Alternate_Hierarchy_Related_Features.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Alternate_Hierarchy_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Alternate_Hierarchy_Related_Features.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_ALTERNATE_HIERARCHY_RELATED_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Alternate_Hierarchy_Related_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Alternate_Hierarchy_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Alternate_Hierarchy_Related_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Alternate_Hierarchy_Related_Geometry.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Alternate_Hierarchy_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Alternate_Hierarchy_Related_Geometry.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_ANIMATION_BEHAVIOUR:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Animation_Behaviour.period: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Animation_Behaviour.period));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Animation_Behaviour.count: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Animation_Behaviour.count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Animation_Behaviour.forward_sequence_mode:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Animation_Behaviour.forward_sequence_mode));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Animation_Behaviour.beginning_frame:"\
                        " %s\n", name_ptr, SE_PrintShortIntegerPositive
                        (field_ptr->u.Animation_Behaviour.beginning_frame));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Animation_Behaviour.ending_frame: %s\n",
                        name_ptr, SE_PrintShortIntegerPositive
                        (field_ptr->u.Animation_Behaviour.ending_frame));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Animation_Behaviour.random_beginning_frame:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Animation_Behaviour.random_beginning_frame));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "period: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Animation_Behaviour.period));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "count: %s\n", SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Animation_Behaviour.count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "forward_sequence_mode: %s\n",SE_PrintBoolean
                    (field_ptr->u.Animation_Behaviour.forward_sequence_mode));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "beginning_frame: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Animation_Behaviour.beginning_frame));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "ending_frame: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Animation_Behaviour.ending_frame));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "random_beginning_frame: %s\n",SE_PrintBoolean
                    (field_ptr->u.Animation_Behaviour.random_beginning_frame));
            }
            break;

        case SE_CLS_DRM_ANIMATION_RELATED_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Animation_Related_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Animation_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Animation_Related_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Animation_Related_Geometry.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Animation_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Animation_Related_Geometry.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_ARC:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Arc.count: %s\n", name_ptr,
                        SE_PrintShortIntegerUnsigned(field_ptr->u.Arc.count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Arc.suppress_last: %s\n",name_ptr,
                        SE_PrintBoolean(field_ptr->u.Arc.suppress_last));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "count: %s\n", SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Arc.count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "suppress_last: %s\n",SE_PrintBoolean
                    (field_ptr->u.Arc.suppress_last));
            }
            break;

        case SE_CLS_DRM_AXIS:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Axis.axis_type: %s\n",name_ptr,
                        EDCS_PrintAttributeCode(field_ptr->u.Axis.axis_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Axis.axis_value_count: %s\n", name_ptr,
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Axis.axis_value_count));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis_type: %s\n",EDCS_PrintAttributeCode
                    (field_ptr->u.Axis.axis_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis_value_count: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Axis.axis_value_count));
            }
            break;

        case SE_CLS_DRM_BASE_POSITIONAL_LIGHT:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Base_Positional_Light.apply_to_children:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Base_Positional_Light.apply_to_children));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Base_Positional_Light.override_positional_lights:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Base_Positional_Light.override_positional_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Base_Positional_Light.override_infinite_lights:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Base_Positional_Light.override_infinite_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Base_Positional_Light.active_light_value:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Base_Positional_Light.active_light_value));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Base_Positional_Light.radius: %s\n",
                        name_ptr, SE_PrintFloat
                        (field_ptr->u.Base_Positional_Light.radius));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Base_Positional_Light.constant_attenuation_factor:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Base_Positional_Light.constant_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Base_Positional_Light.linear_attenuation_factor:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Base_Positional_Light.linear_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Base_Positional_Light.quadratic_attenuation_factor:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Base_Positional_Light.quadratic_attenuation_factor));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "apply_to_children: %s\n",SE_PrintBoolean
                    (field_ptr->u.Base_Positional_Light.apply_to_children));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "override_positional_lights: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Base_Positional_Light.override_positional_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "override_infinite_lights: %s\n",SE_PrintBoolean
                    (field_ptr->u.Base_Positional_Light.override_infinite_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "active_light_value: %s\n",SE_PrintBoolean
                    (field_ptr->u.Base_Positional_Light.active_light_value));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "radius: %s\n", SE_PrintFloat
                        (field_ptr->u.Base_Positional_Light.radius));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "constant_attenuation_factor: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Base_Positional_Light.constant_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "linear_attenuation_factor: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Base_Positional_Light.linear_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "quadratic_attenuation_factor: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Base_Positional_Light.quadratic_attenuation_factor));
            }
            break;

        case SE_CLS_DRM_BASE_SPATIAL_ASSOCIATION_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Base_Spatial_Association_Data.meaning:"\
                        " %s\n",name_ptr, SE_PrintSpatialAssociationMeaningType
                    (field_ptr->u.Base_Spatial_Association_Data.meaning));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "meaning: %s\n",
                        SE_PrintSpatialAssociationMeaningType
                    (field_ptr->u.Base_Spatial_Association_Data.meaning));
            }
            break;

        case SE_CLS_DRM_BASE_SUMMARY_ITEM:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Base_Summary_Item.drm_class: %s\n",
                        name_ptr, SE_PrintDRMClass
                    (field_ptr->u.Base_Summary_Item.drm_class));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "drm_class: %s\n",SE_PrintDRMClass
                    (field_ptr->u.Base_Summary_Item.drm_class));
            }
            break;

        case SE_CLS_DRM_BASE_TIME_DATA:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Base_Time_Data.time_significance: %s\n",
                        name_ptr, SE_PrintTimeSignificance
                    (field_ptr->u.Base_Time_Data.time_significance));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "time_significance: %s\n",
                        SE_PrintTimeSignificance
                    (field_ptr->u.Base_Time_Data.time_significance));
            }
            break;

        case SE_CLS_DRM_BLEND_DIRECTIONAL_LIGHT:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Blend_Directional_Light.upper_plane_angular_offset:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Blend_Directional_Light.upper_plane_angular_offset));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Blend_Directional_Light.lower_plane_angular_offset:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Blend_Directional_Light.lower_plane_angular_offset));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "upper_plane_angular_offset: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Blend_Directional_Light.upper_plane_angular_offset));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "lower_plane_angular_offset: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Blend_Directional_Light.lower_plane_angular_offset));
            }
            break;

        case SE_CLS_DRM_BROWSE_MEDIA:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Browse_Media.name", name_ptr);
                SE_PrintString(&(field_ptr->u.Browse_Media.name), name_buffer,
                  level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Browse_Media.media_format: %s\n",
                        name_ptr, SE_PrintMediaFormat
                    (field_ptr->u.Browse_Media.media_format));
                sprintf(name_buffer,"%s->u.Browse_Media.media_urn", name_ptr);
                SE_PrintURN(&(field_ptr->u.Browse_Media.media_urn),
                  name_buffer, level);
                sprintf(name_buffer,"%s->u.Browse_Media.description",
                        name_ptr);
                SE_PrintString(&(field_ptr->u.Browse_Media.description),
                  name_buffer, level);
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Browse_Media.name), "name",
                  level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "media_format: %s\n",SE_PrintMediaFormat
                    (field_ptr->u.Browse_Media.media_format));
                SE_PrintURN(&(field_ptr->u.Browse_Media.media_urn),
                  "media_urn", level);
                SE_PrintString(&(field_ptr->u.Browse_Media.description),
                  "description", level);
            }
            break;

        case SE_CLS_DRM_CAMERA_POINT:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Camera_Point.projection: %s\n",name_ptr,
                        SE_PrintCameraProjectionType
                    (field_ptr->u.Camera_Point.projection));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Camera_Point.camera_near: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Camera_Point.camera_near));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Camera_Point.camera_far: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Camera_Point.camera_far));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Camera_Point.use_left_bottom_right_top:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Camera_Point.use_left_bottom_right_top));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Camera_Point.left: %s\n", name_ptr,
                        SE_PrintLongFloat(field_ptr->u.Camera_Point.left));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Camera_Point.bottom: %s\n", name_ptr,
                        SE_PrintLongFloat(field_ptr->u.Camera_Point.bottom));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Camera_Point.right: %s\n", name_ptr,
                        SE_PrintLongFloat(field_ptr->u.Camera_Point.right));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Camera_Point.top: %s\n", name_ptr,
                        SE_PrintLongFloat(field_ptr->u.Camera_Point.top));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Camera_Point.horizontal_field_of_view:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Camera_Point.horizontal_field_of_view));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Camera_Point.aspect_ratio: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Camera_Point.aspect_ratio));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "projection: %s\n",SE_PrintCameraProjectionType
                    (field_ptr->u.Camera_Point.projection));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "camera_near: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Camera_Point.camera_near));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "camera_far: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Camera_Point.camera_far));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "use_left_bottom_right_top: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Camera_Point.use_left_bottom_right_top));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "left: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Camera_Point.left));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bottom: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Camera_Point.bottom));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "right: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Camera_Point.right));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "top: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Camera_Point.top));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "horizontal_field_of_view: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Camera_Point.horizontal_field_of_view));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "aspect_ratio: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Camera_Point.aspect_ratio));
            }
            break;

        case SE_CLS_DRM_CC_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.CC_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintEuclidean3DCoordinate
                (&(field_ptr->u.CC_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintEuclidean3DCoordinate
                (&(field_ptr->u.CC_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_CD_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.CD_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintCD3DCoordinate
                (&(field_ptr->u.CD_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintCD3DCoordinate
                (&(field_ptr->u.CD_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_CD_SURFACE_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.CD_Surface_Location.coordinate",
                        name_ptr);
                SRM_PrintCDSurfaceCoordinate
                (&(field_ptr->u.CD_Surface_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintCDSurfaceCoordinate
                (&(field_ptr->u.CD_Surface_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_CITATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Citation.title", name_ptr);
                SE_PrintString(&(field_ptr->u.Citation.title), name_buffer,
                  level);
                sprintf(name_buffer,"%s->u.Citation.edition", name_ptr);
                SE_PrintString(&(field_ptr->u.Citation.edition), name_buffer,
                  level);
                sprintf(name_buffer,"%s->u.Citation.series_name", name_ptr);
                SE_PrintString(&(field_ptr->u.Citation.series_name),
                  name_buffer, level);
                sprintf(name_buffer,"%s->u.Citation.issue_identification",
                        name_ptr);
                SE_PrintString(&(field_ptr->u.Citation.issue_identification),
                  name_buffer, level);
                sprintf(name_buffer,"%s->u.Citation.other_citation_details",
                        name_ptr);
                SE_PrintString(&(field_ptr->u.Citation.other_citation_details),
                  name_buffer, level);
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Citation.title), "title", level);
                SE_PrintString(&(field_ptr->u.Citation.edition), "edition",
                  level);
                SE_PrintString(&(field_ptr->u.Citation.series_name),
                  "series_name", level);
                SE_PrintString(&(field_ptr->u.Citation.issue_identification),
                  "issue_identification", level);
                SE_PrintString(&(field_ptr->u.Citation.other_citation_details),
                  "other_citation_details", level);
            }
            break;

        case SE_CLS_DRM_CLASSIFICATION_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Classification_Data.tag: %s\n",name_ptr,
                        EDCS_PrintClassificationCode
                    (field_ptr->u.Classification_Data.tag));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "tag: %s\n",EDCS_PrintClassificationCode
                    (field_ptr->u.Classification_Data.tag));
            }
            break;

        case SE_CLS_DRM_CLASSIFICATION_RELATED_FEATURES:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Classification_Related_Features.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Classification_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Classification_Related_Features.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Classification_Related_Features.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Classification_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Classification_Related_Features.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_CLASSIFICATION_RELATED_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Classification_Related_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Classification_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Classification_Related_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Classification_Related_Geometry.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Classification_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Classification_Related_Geometry.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_CM_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.CM_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.CM_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.CM_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_CMY_COLOUR:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.CMY_Colour.cmy_data", name_ptr);
                SE_PrintCMYData(&(field_ptr->u.CMY_Colour.cmy_data),
                  name_buffer, level);
            }
            else
            {
                SE_PrintCMYData(&(field_ptr->u.CMY_Colour.cmy_data),
                  "cmy_data", level);
            }
            break;

        case SE_CLS_DRM_CMY_COLOUR_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.CMY_Colour_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.CMY_Colour_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.CMY_Colour_Control_Link.cyan_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.CMY_Colour_Control_Link.cyan_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.CMY_Colour_Control_Link.magenta_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.CMY_Colour_Control_Link.magenta_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.CMY_Colour_Control_Link.yellow_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.CMY_Colour_Control_Link.yellow_expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.CMY_Colour_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "cyan_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.CMY_Colour_Control_Link.cyan_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "magenta_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.CMY_Colour_Control_Link.magenta_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "yellow_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.CMY_Colour_Control_Link.yellow_expression_index));
            }
            break;

        case SE_CLS_DRM_COLOUR:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Colour.colour_mapping", name_ptr);
                SE_PrintColourMapping(&(field_ptr->u.Colour.colour_mapping),
                  name_buffer, level);
            }
            else
            {
                SE_PrintColourMapping(&(field_ptr->u.Colour.colour_mapping),
                  "colour_mapping", level);
            }
            break;

        case SE_CLS_DRM_COLOUR_INDEX:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Colour_Index.colour_mapping",
                        name_ptr);
                SE_PrintColourMapping
                (&(field_ptr->u.Colour_Index.colour_mapping), name_buffer,
                  level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Colour_Index.index: %s\n", name_ptr,
                        SE_PrintIntegerPositive
                        (field_ptr->u.Colour_Index.index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Colour_Index.intensity_level: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Colour_Index.intensity_level));
            }
            else
            {
                SE_PrintColourMapping
                (&(field_ptr->u.Colour_Index.colour_mapping),
                  "colour_mapping", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "index: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Colour_Index.index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "intensity_level: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Colour_Index.intensity_level));
            }
            break;

        case SE_CLS_DRM_COLOUR_INDEX_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Colour_Index_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Colour_Index_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Colour_Index_Control_Link.colour_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Colour_Index_Control_Link.colour_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Colour_Index_Control_Link.intensity_level_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Colour_Index_Control_Link.intensity_level_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Colour_Index_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "colour_index: %s\n", SE_PrintIntegerUnsigned
                        (field_ptr->u.Colour_Index_Control_Link.colour_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "intensity_level_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Colour_Index_Control_Link.intensity_level_index));
            }
            break;

        case SE_CLS_DRM_COLOUR_SHININESS:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Colour_Shininess.shininess: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Colour_Shininess.shininess));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "shininess: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Colour_Shininess.shininess));
            }
            break;

        case SE_CLS_DRM_COLOUR_TABLE_GROUP:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Colour_Table_Group.primary_table_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Colour_Table_Group.primary_table_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Colour_Table_Group.table_size: %s\n",
                        name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Colour_Table_Group.table_size));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "primary_table_index: %s\n",
                        SE_PrintIntegerPositive
                        (field_ptr->u.Colour_Table_Group.primary_table_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "table_size: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Colour_Table_Group.table_size));
            }
            break;

        case SE_CLS_DRM_CONE_DIRECTIONAL_LIGHT:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Cone_Directional_Light.has_plane: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Cone_Directional_Light.has_plane));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Cone_Directional_Light.plane_angular_offset:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Cone_Directional_Light.plane_angular_offset));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Cone_Directional_Light.use_full_intensity:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Cone_Directional_Light.use_full_intensity));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Cone_Directional_Light.minimum_colour_intensity:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Cone_Directional_Light.minimum_colour_intensity));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Cone_Directional_Light.invisible_behind:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Cone_Directional_Light.invisible_behind));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "has_plane: %s\n",SE_PrintBoolean
                    (field_ptr->u.Cone_Directional_Light.has_plane));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "plane_angular_offset: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Cone_Directional_Light.plane_angular_offset));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "use_full_intensity: %s\n",SE_PrintBoolean
                    (field_ptr->u.Cone_Directional_Light.use_full_intensity));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "minimum_colour_intensity: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Cone_Directional_Light.minimum_colour_intensity));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "invisible_behind: %s\n",SE_PrintBoolean
                    (field_ptr->u.Cone_Directional_Light.invisible_behind));
            }
            break;

        case SE_CLS_DRM_CONFORMAL_BEHAVIOUR:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Conformal_Behaviour.classification:"\
                        " %s\n",name_ptr, EDCS_PrintClassificationCode
                    (field_ptr->u.Conformal_Behaviour.classification));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Conformal_Behaviour.parallel_gravity:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Conformal_Behaviour.parallel_gravity));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Conformal_Behaviour.offset_distance:"\
                        " %s\n", name_ptr, SE_PrintFloat
                        (field_ptr->u.Conformal_Behaviour.offset_distance));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "classification: %s\n",
                        EDCS_PrintClassificationCode
                    (field_ptr->u.Conformal_Behaviour.classification));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "parallel_gravity: %s\n",SE_PrintBoolean
                    (field_ptr->u.Conformal_Behaviour.parallel_gravity));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "offset_distance: %s\n", SE_PrintFloat
                        (field_ptr->u.Conformal_Behaviour.offset_distance));
            }
            break;

        case SE_CLS_DRM_CONTINUOUS_LOD_RELATED_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Continuous_LOD_Related_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Continuous_LOD_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Continuous_LOD_Related_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Continuous_LOD_Related_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Continuous_LOD_Related_Geometry.terminating_node:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Continuous_LOD_Related_Geometry.terminating_node));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Continuous_LOD_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Continuous_LOD_Related_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "terminating_node: %s\n",SE_PrintBoolean
                    (field_ptr->u.Continuous_LOD_Related_Geometry.terminating_node));
            }
            break;

        case SE_CLS_DRM_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Control_Link.description",
                        name_ptr);
                SE_PrintString(&(field_ptr->u.Control_Link.description),
                  name_buffer, level);
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Control_Link.description),
                  "description", level);
            }
            break;

        case SE_CLS_DRM_CYLINDRICAL_VOLUME_EXTENT:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Cylindrical_Volume_Extent.major_axis_radius:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Cylindrical_Volume_Extent.major_axis_radius));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Cylindrical_Volume_Extent.minor_axis_radius:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Cylindrical_Volume_Extent.minor_axis_radius));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Cylindrical_Volume_Extent.cylinder_length:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Cylindrical_Volume_Extent.cylinder_length));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "major_axis_radius: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Cylindrical_Volume_Extent.major_axis_radius));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "minor_axis_radius: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Cylindrical_Volume_Extent.minor_axis_radius));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "cylinder_length: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Cylindrical_Volume_Extent.cylinder_length));
            }
            break;

        case SE_CLS_DRM_DATA_QUALITY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Data_Quality.fictional: %s\n",name_ptr,
                        SE_PrintBoolean(field_ptr->u.Data_Quality.fictional));
                sprintf(name_buffer,"%s->u.Data_Quality.field_accuracy",
                        name_ptr);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.field_accuracy), name_buffer,
                  level);
                sprintf(name_buffer,"%s->u.Data_Quality.logical_consistency",
                        name_ptr);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.logical_consistency),
                  name_buffer, level);
                sprintf(name_buffer,"%s->u.Data_Quality.completeness",
                        name_ptr);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.completeness), name_buffer,
                  level);
                sprintf(name_buffer,
                        "%s->u.Data_Quality.abs_horiz_pos_accuracy",
                        name_ptr);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.abs_horiz_pos_accuracy),
                  name_buffer, level);
                sprintf(name_buffer,
                        "%s->u.Data_Quality.rel_horiz_pos_accuracy",
                        name_ptr);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.rel_horiz_pos_accuracy),
                  name_buffer, level);
                sprintf(name_buffer,
                        "%s->u.Data_Quality.abs_vert_pos_accuracy", name_ptr);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.abs_vert_pos_accuracy),
                  name_buffer, level);
                sprintf(name_buffer,
                        "%s->u.Data_Quality.rel_vert_pos_accuracy", name_ptr);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.rel_vert_pos_accuracy),
                  name_buffer, level);
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "fictional: %s\n",SE_PrintBoolean
                    (field_ptr->u.Data_Quality.fictional));
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.field_accuracy),
                  "field_accuracy", level);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.logical_consistency),
                  "logical_consistency", level);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.completeness), "completeness",
                  level);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.abs_horiz_pos_accuracy),
                  "abs_horiz_pos_accuracy", level);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.rel_horiz_pos_accuracy),
                  "rel_horiz_pos_accuracy", level);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.abs_vert_pos_accuracy),
                  "abs_vert_pos_accuracy", level);
                SE_PrintDataQualityElement
                (&(field_ptr->u.Data_Quality.rel_vert_pos_accuracy),
                  "rel_vert_pos_accuracy", level);
            }
            break;

        case SE_CLS_DRM_DISTANCE_LOD_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Distance_LOD_Data.minimum_range: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Distance_LOD_Data.minimum_range));
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Distance_LOD_Data.minimum_fade_band:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Distance_LOD_Data.minimum_fade_band));
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Distance_LOD_Data.maximum_range: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Distance_LOD_Data.maximum_range));
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Distance_LOD_Data.maximum_fade_band:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Distance_LOD_Data.maximum_fade_band));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "minimum_range: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Distance_LOD_Data.minimum_range));
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "minimum_fade_band: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Distance_LOD_Data.minimum_fade_band));
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "maximum_range: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Distance_LOD_Data.maximum_range));
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "maximum_fade_band: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Distance_LOD_Data.maximum_fade_band));
            }
            break;

        case SE_CLS_DRM_DRM_CLASS_SUMMARY_ITEM:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.DRM_Class_Summary_Item.drm_class: %s\n",
                        name_ptr, SE_PrintDRMClass
                    (field_ptr->u.DRM_Class_Summary_Item.drm_class));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "drm_class: %s\n",SE_PrintDRMClass
                    (field_ptr->u.DRM_Class_Summary_Item.drm_class));
            }
            break;

        case SE_CLS_DRM_EC_AUGMENTED_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.EC_Augmented_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintMapProjection3DCoordinate
                (&(field_ptr->u.EC_Augmented_3D_Location.coordinate),
                  name_buffer, level);
            }
            else
            {
                SRM_PrintMapProjection3DCoordinate
                (&(field_ptr->u.EC_Augmented_3D_Location.coordinate),
                  "coordinate", level);
            }
            break;

        case SE_CLS_DRM_EC_SURFACE_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.EC_Surface_Location.coordinate",
                        name_ptr);
                SRM_PrintMapProjectionSurfaceCoordinate
                (&(field_ptr->u.EC_Surface_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintMapProjectionSurfaceCoordinate
                (&(field_ptr->u.EC_Surface_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_EDCS_USE_SUMMARY_ITEM:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.EDCS_Use_Summary_Item.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.EDCS_Use_Summary_Item.description),
                  name_buffer, level);
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.EDCS_Use_Summary_Item.description),
                  "description", level);
            }
            break;

        case SE_CLS_DRM_EDGE_DIRECTION:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Edge_Direction.forwards: %s\n",name_ptr,
                        SE_PrintBoolean(field_ptr->u.Edge_Direction.forwards));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "forwards: %s\n",SE_PrintBoolean
                    (field_ptr->u.Edge_Direction.forwards));
            }
            break;

        case SE_CLS_DRM_EI_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.EI_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintEI3DCoordinate
                (&(field_ptr->u.EI_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintEI3DCoordinate
                (&(field_ptr->u.EI_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_ELLIPSE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Ellipse.major_axis_length: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Ellipse.major_axis_length));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Ellipse.minor_axis_length: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Ellipse.minor_axis_length));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "major_axis_length: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Ellipse.major_axis_length));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "minor_axis_length: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Ellipse.minor_axis_length));
            }
            break;

        case SE_CLS_DRM_ENUMERATION_AXIS:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Enumeration_Axis.axis_type: %s\n",
                        name_ptr, EDCS_PrintAttributeCode
                    (field_ptr->u.Enumeration_Axis.axis_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Enumeration_Axis.axis_value_count: %s\n",
                        name_ptr, SE_PrintShortIntegerPositive
                        (field_ptr->u.Enumeration_Axis.axis_value_count));
                if ((field_ptr->u.Enumeration_Axis.axis_value_count > 0) &&
                    (field_ptr->u.Enumeration_Axis.axis_value_array != NULL))
                {
                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Enumeration_Axis.axis_value_count; i++)
                    {
                        SE_Indent(level, f_ptr);
                        fprintf(f_ptr, 
                                "%s->u.Enumeration_Axis.axis_value_array[%u]:"\
                                " %s\n", name_ptr, i, EDCS_PrintEnumerantCode
                                (field_ptr->u.Enumeration_Axis.axis_type,
                                field_ptr->u.Enumeration_Axis.axis_value_array[i]));
                    } /* end for i */
                }
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis_type: %s\n",EDCS_PrintAttributeCode
                    (field_ptr->u.Enumeration_Axis.axis_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis_value_count: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Enumeration_Axis.axis_value_count));
                if ((field_ptr->u.Enumeration_Axis.axis_value_count > 0) &&
                    (field_ptr->u.Enumeration_Axis.axis_value_array != NULL))
                {
                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Enumeration_Axis.axis_value_count; i++)
                    {
                        SE_Indent(level, f_ptr);
                        fprintf(f_ptr, "axis_value_array[%u]: %s\n", i,
                                EDCS_PrintEnumerantCode
                                (field_ptr->u.Enumeration_Axis.axis_type,
                                field_ptr->u.Enumeration_Axis.axis_value_array[i]));
                    } /* end for i */
                }
            }
            break;

        case SE_CLS_DRM_ENVIRONMENT_ROOT:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Environment_Root.srf_context_info",
                        name_ptr);
                SE_PrintSRFContextInfo
                (&(field_ptr->u.Environment_Root.srf_context_info),
                  name_buffer, level);
            }
            else
            {
                SE_PrintSRFContextInfo
                (&(field_ptr->u.Environment_Root.srf_context_info),
                  "srf_context_info", level);
            }
            break;

        case SE_CLS_DRM_ENVIRONMENTAL_DOMAIN_SUMMARY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Environmental_Domain_Summary.environmental_domain:"\
                        " %s\n",name_ptr, EDCS_PrintClassificationCode
                    (field_ptr->u.Environmental_Domain_Summary.environmental_domain));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "environmental_domain: %s\n",
                        EDCS_PrintClassificationCode
                    (field_ptr->u.Environmental_Domain_Summary.environmental_domain));
            }
            break;

        case SE_CLS_DRM_FACE_DIRECTION:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Face_Direction.front: %s\n",name_ptr,
                        SE_PrintBoolean(field_ptr->u.Face_Direction.front));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "front: %s\n",SE_PrintBoolean
                    (field_ptr->u.Face_Direction.front));
            }
            break;

        case SE_CLS_DRM_FADE_RANGE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Fade_Range.fade_to_off_begin: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Fade_Range.fade_to_off_begin));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Fade_Range.fade_to_off_complete: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Fade_Range.fade_to_off_complete));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "fade_to_off_begin: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Fade_Range.fade_to_off_begin));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "fade_to_off_complete: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Fade_Range.fade_to_off_complete));
            }
            break;

        case SE_CLS_DRM_FEATURE_FACE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Feature_Face.universal: %s\n",name_ptr,
                        SE_PrintBoolean(field_ptr->u.Feature_Face.universal));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "universal: %s\n",SE_PrintBoolean
                    (field_ptr->u.Feature_Face.universal));
            }
            break;

        case SE_CLS_DRM_FEATURE_TOPOLOGY_HIERARCHY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Feature_Topology_Hierarchy.feature_topology_level:"\
                        " %s\n",name_ptr, SE_PrintFeatureTopologyLevel
                    (field_ptr->u.Feature_Topology_Hierarchy.feature_topology_level));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "feature_topology_level: %s\n",
                        SE_PrintFeatureTopologyLevel
                    (field_ptr->u.Feature_Topology_Hierarchy.feature_topology_level));
            }
            break;

        case SE_CLS_DRM_FEATURE_VOLUME:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Feature_Volume.universal: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Feature_Volume.universal));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "universal: %s\n",SE_PrintBoolean
                    (field_ptr->u.Feature_Volume.universal));
            }
            break;

        case SE_CLS_DRM_FLASHING_LIGHT_BEHAVIOUR:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Flashing_Light_Behaviour.period: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Flashing_Light_Behaviour.period));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Flashing_Light_Behaviour.delay: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Flashing_Light_Behaviour.delay));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Flashing_Light_Behaviour.duration: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Flashing_Light_Behaviour.duration));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "period: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Flashing_Light_Behaviour.period));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delay: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Flashing_Light_Behaviour.delay));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "duration: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Flashing_Light_Behaviour.duration));
            }
            break;

        case SE_CLS_DRM_FUNCTION:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Function.value_type: %s\n",name_ptr,
                        EDCS_PrintAttributeValueType
                    (field_ptr->u.Function.value_type));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_type: %s\n",EDCS_PrintAttributeValueType
                    (field_ptr->u.Function.value_type));
            }
            break;

        case SE_CLS_DRM_FUNCTIONAL_ASSOCIATION_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Functional_Association_Data.meaning:"\
                        " %s\n",name_ptr,
                        SE_PrintFunctionalAssociationMeaningType
                    (field_ptr->u.Functional_Association_Data.meaning));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "meaning: %s\n",
                        SE_PrintFunctionalAssociationMeaningType
                    (field_ptr->u.Functional_Association_Data.meaning));
            }
            break;

        case SE_CLS_DRM_GEOMETRIC_CENTRE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Geometric_Centre.meaning: %s\n",
                        name_ptr, SE_PrintGeometricCentreCode
                    (field_ptr->u.Geometric_Centre.meaning));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "meaning: %s\n",SE_PrintGeometricCentreCode
                    (field_ptr->u.Geometric_Centre.meaning));
            }
            break;

        case SE_CLS_DRM_GEOMETRY_TOPOLOGY_HIERARCHY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Geometry_Topology_Hierarchy.geometry_topology_level:"\
                        " %s\n",name_ptr, SE_PrintGeometryTopologyLevel
                    (field_ptr->u.Geometry_Topology_Hierarchy.geometry_topology_level));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "geometry_topology_level: %s\n",
                        SE_PrintGeometryTopologyLevel
                    (field_ptr->u.Geometry_Topology_Hierarchy.geometry_topology_level));
            }
            break;

        case SE_CLS_DRM_GRID_OVERLAP:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Grid_Overlap.overlay_group: %s\n",
                        name_ptr, SE_PrintShortIntegerPositive
                        (field_ptr->u.Grid_Overlap.overlay_group));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Grid_Overlap.priority: %s\n", name_ptr,
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Grid_Overlap.priority));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Grid_Overlap.operation: %s\n",name_ptr,
                        SE_PrintGridOverlapOperator
                    (field_ptr->u.Grid_Overlap.operation));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "overlay_group: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Grid_Overlap.overlay_group));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "priority: %s\n", SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Grid_Overlap.priority));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "operation: %s\n",SE_PrintGridOverlapOperator
                    (field_ptr->u.Grid_Overlap.operation));
            }
            break;

        case SE_CLS_DRM_HAEC_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.HAEC_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.HAEC_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.HAEC_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_HEEC_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.HEEC_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.HEEC_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.HEEC_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_HEEQ_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.HEEQ_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.HEEQ_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.HEEQ_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_HIERARCHY_DATA:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Hierarchy_Data.alternate_representation_reason",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Hierarchy_Data.alternate_representation_reason),
                  name_buffer, level);
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Hierarchy_Data.alternate_representation_reason),
                  "alternate_representation_reason", level);
            }
            break;

        case SE_CLS_DRM_HIERARCHY_SUMMARY_ITEM:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Hierarchy_Summary_Item.drm_class: %s\n",
                        name_ptr, SE_PrintDRMClass
                    (field_ptr->u.Hierarchy_Summary_Item.drm_class));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Hierarchy_Summary_Item.multiplicity_meaning:"\
                        " %s\n",name_ptr, SE_PrintHSMultiplicityCode
                    (field_ptr->u.Hierarchy_Summary_Item.multiplicity_meaning));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Hierarchy_Summary_Item.multiplicity:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Hierarchy_Summary_Item.multiplicity));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "drm_class: %s\n",SE_PrintDRMClass
                    (field_ptr->u.Hierarchy_Summary_Item.drm_class));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "multiplicity_meaning: %s\n",
                        SE_PrintHSMultiplicityCode
                    (field_ptr->u.Hierarchy_Summary_Item.multiplicity_meaning));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "multiplicity: %s\n", SE_PrintIntegerUnsigned
                        (field_ptr->u.Hierarchy_Summary_Item.multiplicity));
            }
            break;

        case SE_CLS_DRM_HSV_COLOUR:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.HSV_Colour.hsv_data", name_ptr);
                SE_PrintHSVData(&(field_ptr->u.HSV_Colour.hsv_data),
                  name_buffer, level);
            }
            else
            {
                SE_PrintHSVData(&(field_ptr->u.HSV_Colour.hsv_data),
                  "hsv_data", level);
            }
            break;

        case SE_CLS_DRM_HSV_COLOUR_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.HSV_Colour_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.HSV_Colour_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.HSV_Colour_Control_Link.hue_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.HSV_Colour_Control_Link.hue_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.HSV_Colour_Control_Link.saturation_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.HSV_Colour_Control_Link.saturation_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.HSV_Colour_Control_Link.value_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.HSV_Colour_Control_Link.value_expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.HSV_Colour_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "hue_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.HSV_Colour_Control_Link.hue_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "saturation_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.HSV_Colour_Control_Link.saturation_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.HSV_Colour_Control_Link.value_expression_index));
            }
            break;

        case SE_CLS_DRM_IDENTIFICATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Identification.abstract", name_ptr);
                SE_PrintString(&(field_ptr->u.Identification.abstract),
                  name_buffer, level);
                sprintf(name_buffer,"%s->u.Identification.purpose", name_ptr);
                SE_PrintString(&(field_ptr->u.Identification.purpose),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Identification.credit_count: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Identification.credit_count));
                if ((field_ptr->u.Identification.credit_count > 0) &&
                    (field_ptr->u.Identification.credit != NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Identification.credit_count; i++)
                    {
                        sprintf(buffer, "%s->u.Identification.credit[%u]", name_ptr, i);
                        SE_PrintString
                           (&(field_ptr->u.Identification.credit[i]), buffer,
                           level);
                    } /* end for i */
                }
                sprintf(name_buffer,
                        "%s->u.Identification.supplemental_information",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Identification.supplemental_information),
                  name_buffer, level);
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Identification.abstract),
                  "abstract", level);
                SE_PrintString(&(field_ptr->u.Identification.purpose),
                  "purpose", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "credit_count: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Identification.credit_count));
                if ((field_ptr->u.Identification.credit_count > 0) &&
                    (field_ptr->u.Identification.credit != NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Identification.credit_count; i++)
                    {
                        sprintf(buffer, "credit[%u]", i);
                        SE_PrintString
                           (&(field_ptr->u.Identification.credit[i]), buffer,
                           level);
                    } /* end for i */
                }
                SE_PrintString
                (&(field_ptr->u.Identification.supplemental_information),
                  "supplemental_information", level);
            }
            break;

        case SE_CLS_DRM_IMAGE:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Image.name", name_ptr);
                SE_PrintString(&(field_ptr->u.Image.name), name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.colour_model: %s\n",name_ptr,
                        SE_PrintColourModel(field_ptr->u.Image.colour_model));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.level_count: %s\n", name_ptr,
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Image.level_count));
                if ((field_ptr->u.Image.level_count > 0) &&
                    (field_ptr->u.Image.mip_extents_array != NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Image.level_count; i++)
                    {
                        sprintf(buffer, "%s->u.Image.mip_extents_array[%u]", name_ptr, i);
                        SE_PrintImageMIPExtents
                           (&(field_ptr->u.Image.mip_extents_array[i]),
                           buffer, level);
                    } /* end for i */
                }
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.image_signature: %s\n",name_ptr,
                        SE_PrintImageSignature
                    (field_ptr->u.Image.image_signature));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.scan_direction: %s\n",name_ptr,
                        SE_PrintImageScanDirection
                    (field_ptr->u.Image.scan_direction));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.scan_direction_z: %s\n",name_ptr,
                        SE_PrintImageScanDirectionZ
                    (field_ptr->u.Image.scan_direction_z));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.component_data_type: %s\n",
                        name_ptr, SE_PrintImageComponentType
                    (field_ptr->u.Image.component_data_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.data_is_little_endian: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Image.data_is_little_endian));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.data_is_3D: %s\n",name_ptr,
                        SE_PrintBoolean(field_ptr->u.Image.data_is_3D));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_alpha: %s\n", name_ptr,
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_alpha));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_luminance: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_luminance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_colour_coordinate_1: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_colour_coordinate_1));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_colour_coordinate_2: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_colour_coordinate_2));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_colour_coordinate_3: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_colour_coordinate_3));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_bump_map_height: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_bump_map_height));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_material_1: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_material_1));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_material_2: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_material_2));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_material_3: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_material_3));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_material_2_percentage:"\
                        " %s\n", name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_material_2_percentage));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_material_3_percentage:"\
                        " %s\n", name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_material_3_percentage));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_image_index: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_image_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_bump_map_u: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_bump_map_u));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.bits_of_bump_map_v: %s\n",
                        name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_bump_map_v));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.min_value_of_alpha: %s\n",
                        name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_alpha));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.max_value_of_alpha: %s\n",
                        name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_alpha));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.min_value_of_luminance: %s\n",
                        name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_luminance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.max_value_of_luminance: %s\n",
                        name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_luminance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Image.min_value_of_colour_coordinate_1:"\
                        " %s\n", name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_colour_coordinate_1));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Image.max_value_of_colour_coordinate_1:"\
                        " %s\n", name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_colour_coordinate_1));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Image.min_value_of_colour_coordinate_2:"\
                        " %s\n", name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_colour_coordinate_2));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Image.max_value_of_colour_coordinate_2:"\
                        " %s\n", name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_colour_coordinate_2));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Image.min_value_of_colour_coordinate_3:"\
                        " %s\n", name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_colour_coordinate_3));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Image.max_value_of_colour_coordinate_3:"\
                        " %s\n", name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_colour_coordinate_3));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.min_value_of_bump_map_height:"\
                        " %s\n", name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_bump_map_height));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.max_value_of_bump_map_height:"\
                        " %s\n", name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_bump_map_height));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.min_value_of_bump_map_u: %s\n",
                        name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_bump_map_u));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.max_value_of_bump_map_u: %s\n",
                        name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_bump_map_u));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.min_value_of_bump_map_v: %s\n",
                        name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_bump_map_v));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image.max_value_of_bump_map_v: %s\n",
                        name_ptr, SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_bump_map_v));
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Image.name), "name", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "colour_model: %s\n",SE_PrintColourModel
                    (field_ptr->u.Image.colour_model));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "level_count: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Image.level_count));
                if ((field_ptr->u.Image.level_count > 0) &&
                    (field_ptr->u.Image.mip_extents_array != NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Image.level_count; i++)
                    {
                        sprintf(buffer, "mip_extents_array[%u]", i);
                        SE_PrintImageMIPExtents
                           (&(field_ptr->u.Image.mip_extents_array[i]),
                           buffer, level);
                    } /* end for i */
                }
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "image_signature: %s\n",SE_PrintImageSignature
                    (field_ptr->u.Image.image_signature));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "scan_direction: %s\n",
                        SE_PrintImageScanDirection
                    (field_ptr->u.Image.scan_direction));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "scan_direction_z: %s\n",
                        SE_PrintImageScanDirectionZ
                    (field_ptr->u.Image.scan_direction_z));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "component_data_type: %s\n",
                        SE_PrintImageComponentType
                    (field_ptr->u.Image.component_data_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "data_is_little_endian: %s\n",SE_PrintBoolean
                    (field_ptr->u.Image.data_is_little_endian));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "data_is_3D: %s\n",SE_PrintBoolean
                    (field_ptr->u.Image.data_is_3D));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_alpha: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_alpha));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_luminance: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_luminance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_colour_coordinate_1: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_colour_coordinate_1));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_colour_coordinate_2: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_colour_coordinate_2));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_colour_coordinate_3: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_colour_coordinate_3));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_bump_map_height: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_bump_map_height));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_material_1: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_material_1));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_material_2: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_material_2));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_material_3: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_material_3));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_material_2_percentage: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_material_2_percentage));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_material_3_percentage: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_material_3_percentage));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_image_index: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_image_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_bump_map_u: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_bump_map_u));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_of_bump_map_v: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Image.bits_of_bump_map_v));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "min_value_of_alpha: %s\n", SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_alpha));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "max_value_of_alpha: %s\n", SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_alpha));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "min_value_of_luminance: %s\n", SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_luminance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "max_value_of_luminance: %s\n", SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_luminance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "min_value_of_colour_coordinate_1: %s\n",
                        SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_colour_coordinate_1));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "max_value_of_colour_coordinate_1: %s\n",
                        SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_colour_coordinate_1));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "min_value_of_colour_coordinate_2: %s\n",
                        SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_colour_coordinate_2));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "max_value_of_colour_coordinate_2: %s\n",
                        SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_colour_coordinate_2));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "min_value_of_colour_coordinate_3: %s\n",
                        SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_colour_coordinate_3));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "max_value_of_colour_coordinate_3: %s\n",
                        SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_colour_coordinate_3));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "min_value_of_bump_map_height: %s\n",
                        SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_bump_map_height));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "max_value_of_bump_map_height: %s\n",
                        SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_bump_map_height));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "min_value_of_bump_map_u: %s\n", SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_bump_map_u));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "max_value_of_bump_map_u: %s\n", SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_bump_map_u));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "min_value_of_bump_map_v: %s\n", SE_PrintFloat
                        (field_ptr->u.Image.min_value_of_bump_map_v));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "max_value_of_bump_map_v: %s\n", SE_PrintFloat
                        (field_ptr->u.Image.max_value_of_bump_map_v));
            }
            break;

        case SE_CLS_DRM_IMAGE_ANCHOR:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Image_Anchor.srf_context_info",
                        name_ptr);
                SE_PrintSRFContextInfo
                (&(field_ptr->u.Image_Anchor.srf_context_info), name_buffer,
                  level);
            }
            else
            {
                SE_PrintSRFContextInfo
                (&(field_ptr->u.Image_Anchor.srf_context_info),
                  "srf_context_info", level);
            }
            break;

        case SE_CLS_DRM_IMAGE_MAPPING_FUNCTION:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Image_Mapping_Function.image_mapping_method:"\
                        " %s\n",name_ptr, SE_PrintImageMappingMethod
                    (field_ptr->u.Image_Mapping_Function.image_mapping_method));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image_Mapping_Function.image_wrap_s:"\
                        " %s\n",name_ptr, SE_PrintImageWrap
                    (field_ptr->u.Image_Mapping_Function.image_wrap_s));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image_Mapping_Function.image_wrap_t:"\
                        " %s\n",name_ptr, SE_PrintImageWrap
                    (field_ptr->u.Image_Mapping_Function.image_wrap_t));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Image_Mapping_Function.image_projection_type:"\
                        " %s\n",name_ptr, SE_PrintImageProjectionType
                    (field_ptr->u.Image_Mapping_Function.image_projection_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Image_Mapping_Function.intensity_level:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Image_Mapping_Function.intensity_level));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Image_Mapping_Function.gain: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Image_Mapping_Function.gain));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Image_Mapping_Function.image_detail_mapping:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Image_Mapping_Function.image_detail_mapping));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "image_mapping_method: %s\n",
                        SE_PrintImageMappingMethod
                    (field_ptr->u.Image_Mapping_Function.image_mapping_method));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "image_wrap_s: %s\n",SE_PrintImageWrap
                    (field_ptr->u.Image_Mapping_Function.image_wrap_s));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "image_wrap_t: %s\n",SE_PrintImageWrap
                    (field_ptr->u.Image_Mapping_Function.image_wrap_t));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "image_projection_type: %s\n",
                        SE_PrintImageProjectionType
                    (field_ptr->u.Image_Mapping_Function.image_projection_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "intensity_level: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Image_Mapping_Function.intensity_level));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "gain: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Image_Mapping_Function.gain));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "image_detail_mapping: %s\n",SE_PrintBoolean
                    (field_ptr->u.Image_Mapping_Function.image_detail_mapping));
            }
            break;

        case SE_CLS_DRM_IN_OUT:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.In_Out.input: %s\n",name_ptr,
                        SE_PrintBoolean(field_ptr->u.In_Out.input));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "input: %s\n",SE_PrintBoolean
                    (field_ptr->u.In_Out.input));
            }
            break;

        case SE_CLS_DRM_INDEX_LOD_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Index_LOD_Data.index: %s\n", name_ptr,
                        SE_PrintIntegerPositive
                        (field_ptr->u.Index_LOD_Data.index));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "index: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Index_LOD_Data.index));
            }
            break;

        case SE_CLS_DRM_INFINITE_LIGHT:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Infinite_Light.apply_to_children: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Infinite_Light.apply_to_children));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Infinite_Light.override_positional_lights:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Infinite_Light.override_positional_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Infinite_Light.override_infinite_lights:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Infinite_Light.override_infinite_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Infinite_Light.active_light_value: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Infinite_Light.active_light_value));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "apply_to_children: %s\n",SE_PrintBoolean
                    (field_ptr->u.Infinite_Light.apply_to_children));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "override_positional_lights: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Infinite_Light.override_positional_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "override_infinite_lights: %s\n",SE_PrintBoolean
                    (field_ptr->u.Infinite_Light.override_infinite_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "active_light_value: %s\n",SE_PrintBoolean
                    (field_ptr->u.Infinite_Light.active_light_value));
            }
            break;

        case SE_CLS_DRM_INLINE_COLOUR:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Inline_Colour.colour_mapping",
                        name_ptr);
                SE_PrintColourMapping
                (&(field_ptr->u.Inline_Colour.colour_mapping), name_buffer,
                  level);
            }
            else
            {
                SE_PrintColourMapping
                (&(field_ptr->u.Inline_Colour.colour_mapping),
                  "colour_mapping", level);
            }
            break;

        case SE_CLS_DRM_INTERFACE_TEMPLATE:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Interface_Template.description",
                        name_ptr);
                SE_PrintString(&(field_ptr->u.Interface_Template.description),
                  name_buffer, level);
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Interface_Template.description),
                  "description", level);
            }
            break;

        case SE_CLS_DRM_INTERVAL_AXIS:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Interval_Axis.axis_type: %s\n",name_ptr,
                        EDCS_PrintAttributeCode
                    (field_ptr->u.Interval_Axis.axis_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Interval_Axis.axis_value_count: %s\n",
                        name_ptr, SE_PrintShortIntegerPositive
                        (field_ptr->u.Interval_Axis.axis_value_count));
                if ((field_ptr->u.Interval_Axis.axis_value_count > 0) &&
                    (field_ptr->u.Interval_Axis.axis_interval_value_array !=
                    NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Interval_Axis.axis_value_count; i++)
                    {
                        sprintf(buffer, "%s->u.Interval_Axis.axis_interval_value_array[%u]", name_ptr, i);
                        SE_PrintIntervalValue
                           (&(field_ptr->u.Interval_Axis.axis_interval_value_array[i]),
                           buffer, level);
                    } /* end for i */
                }
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Interval_Axis.value_unit: %s\n",
                        name_ptr, EDCS_PrintUnitCode
                    (field_ptr->u.Interval_Axis.value_unit));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Interval_Axis.value_scale: %s\n",
                        name_ptr, EDCS_PrintUnitScaleCode
                    (field_ptr->u.Interval_Axis.value_scale));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis_type: %s\n",EDCS_PrintAttributeCode
                    (field_ptr->u.Interval_Axis.axis_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis_value_count: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Interval_Axis.axis_value_count));
                if ((field_ptr->u.Interval_Axis.axis_value_count > 0) &&
                    (field_ptr->u.Interval_Axis.axis_interval_value_array !=
                    NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Interval_Axis.axis_value_count; i++)
                    {
                        sprintf(buffer, "axis_interval_value_array[%u]", i);
                        SE_PrintIntervalValue
                           (&(field_ptr->u.Interval_Axis.axis_interval_value_array[i]),
                           buffer, level);
                    } /* end for i */
                }
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_unit: %s\n",EDCS_PrintUnitCode
                    (field_ptr->u.Interval_Axis.value_unit));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_scale: %s\n",EDCS_PrintUnitScaleCode
                    (field_ptr->u.Interval_Axis.value_scale));
            }
            break;

        case SE_CLS_DRM_IRREGULAR_AXIS:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Irregular_Axis.axis_type: %s\n",
                        name_ptr, EDCS_PrintAttributeCode
                    (field_ptr->u.Irregular_Axis.axis_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Irregular_Axis.axis_value_count: %s\n",
                        name_ptr, SE_PrintShortIntegerPositive
                        (field_ptr->u.Irregular_Axis.axis_value_count));
                if ((field_ptr->u.Irregular_Axis.axis_value_count > 0) &&
                    (field_ptr->u.Irregular_Axis.axis_value_array != NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Irregular_Axis.axis_value_count; i++)
                    {
                        sprintf(buffer, "%s->u.Irregular_Axis.axis_value_array[%u]", name_ptr, i);
                        SE_PrintSingleValue
                           (field_ptr->u.Irregular_Axis.axis_type,
                           &(field_ptr->u.Irregular_Axis.axis_value_array[i]),
                           buffer, level);
                    } /* end for i */
                }
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Irregular_Axis.value_unit: %s\n",
                        name_ptr, EDCS_PrintUnitCode
                    (field_ptr->u.Irregular_Axis.value_unit));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Irregular_Axis.value_scale: %s\n",
                        name_ptr, EDCS_PrintUnitScaleCode
                    (field_ptr->u.Irregular_Axis.value_scale));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Irregular_Axis.interpolation_type: %s\n",
                        name_ptr, SE_PrintInterpolationType
                    (field_ptr->u.Irregular_Axis.interpolation_type));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis_type: %s\n",EDCS_PrintAttributeCode
                    (field_ptr->u.Irregular_Axis.axis_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis_value_count: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Irregular_Axis.axis_value_count));
                if ((field_ptr->u.Irregular_Axis.axis_value_count > 0) &&
                    (field_ptr->u.Irregular_Axis.axis_value_array != NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Irregular_Axis.axis_value_count; i++)
                    {
                        sprintf(buffer, "axis_value_array[%u]", i);
                        SE_PrintSingleValue
                           (field_ptr->u.Irregular_Axis.axis_type,
                           &(field_ptr->u.Irregular_Axis.axis_value_array[i]),
                           buffer, level);
                    } /* end for i */
                }
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_unit: %s\n",EDCS_PrintUnitCode
                    (field_ptr->u.Irregular_Axis.value_unit));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_scale: %s\n",EDCS_PrintUnitScaleCode
                    (field_ptr->u.Irregular_Axis.value_scale));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "interpolation_type: %s\n",
                        SE_PrintInterpolationType
                    (field_ptr->u.Irregular_Axis.interpolation_type));
            }
            break;

        case SE_CLS_DRM_KEYWORDS:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Keywords.keyword_count: %s\n", name_ptr,
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Keywords.keyword_count));
                if ((field_ptr->u.Keywords.keyword_count > 0) &&
                    (field_ptr->u.Keywords.keyword_array != NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Keywords.keyword_count; i++)
                    {
                        sprintf(buffer, "%s->u.Keywords.keyword_array[%u]", name_ptr, i);
                        SE_PrintString
                           (&(field_ptr->u.Keywords.keyword_array[i]), buffer,
                           level);
                    } /* end for i */
                }
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Keywords.type: %s\n",name_ptr,
                        SE_PrintMDKeywordTypeCode(field_ptr->u.Keywords.type));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "keyword_count: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Keywords.keyword_count));
                if ((field_ptr->u.Keywords.keyword_count > 0) &&
                    (field_ptr->u.Keywords.keyword_array != NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Keywords.keyword_count; i++)
                    {
                        sprintf(buffer, "keyword_array[%u]", i);
                        SE_PrintString
                           (&(field_ptr->u.Keywords.keyword_array[i]), buffer,
                           level);
                    } /* end for i */
                }
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "type: %s\n",SE_PrintMDKeywordTypeCode
                    (field_ptr->u.Keywords.type));
            }
            break;

        case SE_CLS_DRM_LCC_AUGMENTED_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.LCC_Augmented_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintMapProjection3DCoordinate
                (&(field_ptr->u.LCC_Augmented_3D_Location.coordinate),
                  name_buffer, level);
            }
            else
            {
                SRM_PrintMapProjection3DCoordinate
                (&(field_ptr->u.LCC_Augmented_3D_Location.coordinate),
                  "coordinate", level);
            }
            break;

        case SE_CLS_DRM_LCC_SURFACE_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.LCC_Surface_Location.coordinate",
                        name_ptr);
                SRM_PrintMapProjectionSurfaceCoordinate
                (&(field_ptr->u.LCC_Surface_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintMapProjectionSurfaceCoordinate
                (&(field_ptr->u.LCC_Surface_Location.coordinate),
                  "coordinate", level);
            }
            break;

        case SE_CLS_DRM_LCE_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.LCE_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintEuclidean3DCoordinate
                (&(field_ptr->u.LCE_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintEuclidean3DCoordinate
                (&(field_ptr->u.LCE_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_LEGAL_CONSTRAINTS:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Legal_Constraints.use_limitation_count:"\
                        " %s\n", name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Legal_Constraints.use_limitation_count));
                if ((field_ptr->u.Legal_Constraints.use_limitation_count > 0)
                    && (field_ptr->u.Legal_Constraints.use_limitation !=
                    NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Legal_Constraints.use_limitation_count;
                        i++)
                    {
                        sprintf(buffer, "%s->u.Legal_Constraints.use_limitation[%u]", name_ptr, i);
                        SE_PrintString
                           (&(field_ptr->u.Legal_Constraints.use_limitation[i]),
                           buffer, level);
                    } /* end for i */
                }
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Legal_Constraints.access_constraints:"\
                        " %s\n",name_ptr, SE_PrintMDRestrictionCode
                    (field_ptr->u.Legal_Constraints.access_constraints));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Legal_Constraints.use_constraints: %s\n",
                        name_ptr, SE_PrintMDRestrictionCode
                    (field_ptr->u.Legal_Constraints.use_constraints));
                sprintf(name_buffer,
                        "%s->u.Legal_Constraints.other_constraints",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Legal_Constraints.other_constraints),
                  name_buffer, level);
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "use_limitation_count: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Legal_Constraints.use_limitation_count));
                if ((field_ptr->u.Legal_Constraints.use_limitation_count > 0)
                    && (field_ptr->u.Legal_Constraints.use_limitation !=
                    NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Legal_Constraints.use_limitation_count;
                        i++)
                    {
                        sprintf(buffer, "use_limitation[%u]", i);
                        SE_PrintString
                           (&(field_ptr->u.Legal_Constraints.use_limitation[i]),
                           buffer, level);
                    } /* end for i */
                }
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "access_constraints: %s\n",
                        SE_PrintMDRestrictionCode
                    (field_ptr->u.Legal_Constraints.access_constraints));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "use_constraints: %s\n",
                        SE_PrintMDRestrictionCode
                    (field_ptr->u.Legal_Constraints.use_constraints));
                SE_PrintString
                (&(field_ptr->u.Legal_Constraints.other_constraints),
                  "other_constraints", level);
            }
            break;

        case SE_CLS_DRM_LIGHT_RENDERING_PROPERTIES:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Light_Rendering_Properties.display_type:"\
                        " %s\n",name_ptr, SE_PrintPointLightDisplayType
                    (field_ptr->u.Light_Rendering_Properties.display_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Light_Rendering_Properties.light_diameter:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Light_Rendering_Properties.light_diameter));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Light_Rendering_Properties.light_extinguishing_range:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Light_Rendering_Properties.light_extinguishing_range));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Light_Rendering_Properties.random_area_light:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Light_Rendering_Properties.random_area_light));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Light_Rendering_Properties.active_light_value:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Light_Rendering_Properties.active_light_value));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Light_Rendering_Properties.candela_value:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Light_Rendering_Properties.candela_value));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "display_type: %s\n",
                        SE_PrintPointLightDisplayType
                    (field_ptr->u.Light_Rendering_Properties.display_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "light_diameter: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Light_Rendering_Properties.light_diameter));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "light_extinguishing_range: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Light_Rendering_Properties.light_extinguishing_range));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "random_area_light: %s\n",SE_PrintBoolean
                    (field_ptr->u.Light_Rendering_Properties.random_area_light));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "active_light_value: %s\n",SE_PrintBoolean
                    (field_ptr->u.Light_Rendering_Properties.active_light_value));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "candela_value: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Light_Rendering_Properties.candela_value));
            }
            break;

        case SE_CLS_DRM_LIGHT_RENDERING_PROPERTIES_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Light_Rendering_Properties_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Light_Rendering_Properties_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Light_Rendering_Properties_Control_Link.active_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Light_Rendering_Properties_Control_Link.active_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Light_Rendering_Properties_Control_Link.candela_value_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Light_Rendering_Properties_Control_Link.candela_value_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Light_Rendering_Properties_Control_Link.lower_candela_value_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Light_Rendering_Properties_Control_Link.lower_candela_value_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Light_Rendering_Properties_Control_Link.upper_candela_value_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Light_Rendering_Properties_Control_Link.upper_candela_value_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Light_Rendering_Properties_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "active_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Light_Rendering_Properties_Control_Link.active_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "candela_value_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Light_Rendering_Properties_Control_Link.candela_value_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "lower_candela_value_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Light_Rendering_Properties_Control_Link.lower_candela_value_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "upper_candela_value_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Light_Rendering_Properties_Control_Link.upper_candela_value_index));
            }
            break;

        case SE_CLS_DRM_LIGHT_SOURCE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Light_Source.apply_to_children: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Light_Source.apply_to_children));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Light_Source.override_positional_lights:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Light_Source.override_positional_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Light_Source.override_infinite_lights:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Light_Source.override_infinite_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Light_Source.active_light_value: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Light_Source.active_light_value));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "apply_to_children: %s\n",SE_PrintBoolean
                    (field_ptr->u.Light_Source.apply_to_children));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "override_positional_lights: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Light_Source.override_positional_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "override_infinite_lights: %s\n",SE_PrintBoolean
                    (field_ptr->u.Light_Source.override_infinite_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "active_light_value: %s\n",SE_PrintBoolean
                    (field_ptr->u.Light_Source.active_light_value));
            }
            break;

        case SE_CLS_DRM_LIGHT_SOURCE_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Light_Source_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Light_Source_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Light_Source_Control_Link.expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Light_Source_Control_Link.expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Light_Source_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "expression_index: %s\n",
                        SE_PrintIntegerPositive
                        (field_ptr->u.Light_Source_Control_Link.expression_index));
            }
            break;

        case SE_CLS_DRM_LINE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Line.count: %s\n", name_ptr,
                        SE_PrintShortIntegerUnsigned(field_ptr->u.Line.count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Line.suppress_last: %s\n",name_ptr,
                        SE_PrintBoolean(field_ptr->u.Line.suppress_last));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "count: %s\n", SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Line.count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "suppress_last: %s\n",SE_PrintBoolean
                    (field_ptr->u.Line.suppress_last));
            }
            break;

        case SE_CLS_DRM_LINEAGE:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Lineage.statement", name_ptr);
                SE_PrintString(&(field_ptr->u.Lineage.statement), name_buffer,
                  level);
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Lineage.statement), "statement",
                  level);
            }
            break;

        case SE_CLS_DRM_LINEAR_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Linear_Geometry.count: %s\n", name_ptr,
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Linear_Geometry.count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Linear_Geometry.suppress_last: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Linear_Geometry.suppress_last));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "count: %s\n", SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Linear_Geometry.count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "suppress_last: %s\n",SE_PrintBoolean
                    (field_ptr->u.Linear_Geometry.suppress_last));
            }
            break;

        case SE_CLS_DRM_LITERAL:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Literal.value", name_ptr);
                SE_PrintSingleValue(EAC_NULL, &(field_ptr->u.Literal.value),
                  name_buffer, level);
            }
            else
            {
                SE_PrintSingleValue(EAC_NULL, &(field_ptr->u.Literal.value),
                  "value", level);
            }
            break;

        case SE_CLS_DRM_LOBE_DATA:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Lobe_Data.horizontal_width: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Lobe_Data.horizontal_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Lobe_Data.vertical_width: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Lobe_Data.vertical_width));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "horizontal_width: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Lobe_Data.horizontal_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "vertical_width: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Lobe_Data.vertical_width));
            }
            break;

        case SE_CLS_DRM_LOCAL_4X4:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Local_4x4.matrix: %s\n", name_ptr,
                        SRM_PrintMatrix4x4(field_ptr->u.Local_4x4.matrix));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "matrix: %s\n", SRM_PrintMatrix4x4
                        (field_ptr->u.Local_4x4.matrix));
            }
            break;

        case SE_CLS_DRM_LOD_RELATED_FEATURES:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.LOD_Related_Features.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.LOD_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.LOD_Related_Features.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.LOD_Related_Features.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.LOD_Related_Features.lod_data_type:"\
                        " %s\n",name_ptr, SE_PrintLODDataType
                    (field_ptr->u.LOD_Related_Features.lod_data_type));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.LOD_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.LOD_Related_Features.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "lod_data_type: %s\n",SE_PrintLODDataType
                    (field_ptr->u.LOD_Related_Features.lod_data_type));
            }
            break;

        case SE_CLS_DRM_LOD_RELATED_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.LOD_Related_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.LOD_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.LOD_Related_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.LOD_Related_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.LOD_Related_Geometry.lod_data_type:"\
                        " %s\n",name_ptr, SE_PrintLODDataType
                    (field_ptr->u.LOD_Related_Geometry.lod_data_type));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.LOD_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.LOD_Related_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "lod_data_type: %s\n",SE_PrintLODDataType
                    (field_ptr->u.LOD_Related_Geometry.lod_data_type));
            }
            break;

        case SE_CLS_DRM_LSA_2D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.LSA_2D_Location.coordinate",
                        name_ptr);
                SRM_PrintLSA2DCoordinate
                (&(field_ptr->u.LSA_2D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintLSA2DCoordinate
                (&(field_ptr->u.LSA_2D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_LSP_2D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.LSP_2D_Location.coordinate",
                        name_ptr);
                SRM_PrintLSP2DCoordinate
                (&(field_ptr->u.LSP_2D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintLSP2DCoordinate
                (&(field_ptr->u.LSP_2D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_LSR_2D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.LSR_2D_Location.coordinate",
                        name_ptr);
                SRM_PrintEuclidean2DCoordinate
                (&(field_ptr->u.LSR_2D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintEuclidean2DCoordinate
                (&(field_ptr->u.LSR_2D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_LSR_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.LSR_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintEuclidean3DCoordinate
                (&(field_ptr->u.LSR_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintEuclidean3DCoordinate
                (&(field_ptr->u.LSR_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_LSR_3D_LOCATION_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.LSR_3D_Location_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.LSR_3D_Location_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.LSR_3D_Location_Control_Link.u_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.LSR_3D_Location_Control_Link.u_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.LSR_3D_Location_Control_Link.v_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.LSR_3D_Location_Control_Link.v_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.LSR_3D_Location_Control_Link.w_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.LSR_3D_Location_Control_Link.w_expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.LSR_3D_Location_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "u_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.LSR_3D_Location_Control_Link.u_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "v_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.LSR_3D_Location_Control_Link.v_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "w_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.LSR_3D_Location_Control_Link.w_expression_index));
            }
            break;

        case SE_CLS_DRM_LTSAS_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.LTSAS_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintLTSAS3DCoordinate
                (&(field_ptr->u.LTSAS_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintLTSAS3DCoordinate
                (&(field_ptr->u.LTSAS_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_LTSAS_SURFACE_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.LTSAS_Surface_Location.coordinate",
                        name_ptr);
                SRM_PrintLTSASSurfaceCoordinate
                (&(field_ptr->u.LTSAS_Surface_Location.coordinate),
                  name_buffer, level);
            }
            else
            {
                SRM_PrintLTSASSurfaceCoordinate
                (&(field_ptr->u.LTSAS_Surface_Location.coordinate),
                  "coordinate", level);
            }
            break;

        case SE_CLS_DRM_LTSC_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.LTSC_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintLTSC3DCoordinate
                (&(field_ptr->u.LTSC_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintLTSC3DCoordinate
                (&(field_ptr->u.LTSC_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_LTSC_SURFACE_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.LTSC_Surface_Location.coordinate",
                        name_ptr);
                SRM_PrintLTSCSurfaceCoordinate
                (&(field_ptr->u.LTSC_Surface_Location.coordinate),
                  name_buffer, level);
            }
            else
            {
                SRM_PrintLTSCSurfaceCoordinate
                (&(field_ptr->u.LTSC_Surface_Location.coordinate),
                  "coordinate", level);
            }
            break;

        case SE_CLS_DRM_LTSE_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.LTSE_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintLTSE3DCoordinate
                (&(field_ptr->u.LTSE_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintLTSE3DCoordinate
                (&(field_ptr->u.LTSE_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_LTSE_SURFACE_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.LTSE_Surface_Location.coordinate",
                        name_ptr);
                SRM_PrintLTSESurfaceCoordinate
                (&(field_ptr->u.LTSE_Surface_Location.coordinate),
                  name_buffer, level);
            }
            else
            {
                SRM_PrintLTSESurfaceCoordinate
                (&(field_ptr->u.LTSE_Surface_Location.coordinate),
                  "coordinate", level);
            }
            break;

        case SE_CLS_DRM_M_AUGMENTED_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.M_Augmented_3D_Location.coordinate", name_ptr);
                SRM_PrintMapProjection3DCoordinate
                (&(field_ptr->u.M_Augmented_3D_Location.coordinate),
                  name_buffer, level);
            }
            else
            {
                SRM_PrintMapProjection3DCoordinate
                (&(field_ptr->u.M_Augmented_3D_Location.coordinate),
                  "coordinate", level);
            }
            break;

        case SE_CLS_DRM_M_SURFACE_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.M_Surface_Location.coordinate",
                        name_ptr);
                SRM_PrintMapProjectionSurfaceCoordinate
                (&(field_ptr->u.M_Surface_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintMapProjectionSurfaceCoordinate
                (&(field_ptr->u.M_Surface_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_MAP_SCALE_LOD_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Map_Scale_LOD_Data.map_scale: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Map_Scale_LOD_Data.map_scale));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "map_scale: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Map_Scale_LOD_Data.map_scale));
            }
            break;

        case SE_CLS_DRM_MESH_FACE_TABLE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Mesh_Face_Table.mesh_face_count: %s\n",
                        name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Mesh_Face_Table.mesh_face_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Mesh_Face_Table.maximum_vertices_per_face:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Mesh_Face_Table.maximum_vertices_per_face));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Mesh_Face_Table.adjacent_face_table_present:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Mesh_Face_Table.adjacent_face_table_present));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "mesh_face_count: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Mesh_Face_Table.mesh_face_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "maximum_vertices_per_face: %s\n",
                        SE_PrintIntegerPositive
                        (field_ptr->u.Mesh_Face_Table.maximum_vertices_per_face));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "adjacent_face_table_present: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Mesh_Face_Table.adjacent_face_table_present));
            }
            break;

        case SE_CLS_DRM_MODEL:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Model.name", name_ptr);
                SE_PrintString(&(field_ptr->u.Model.name), name_buffer, level);
                sprintf(name_buffer,"%s->u.Model.srf_context_info", name_ptr);
                SE_PrintSRFContextInfo(&(field_ptr->u.Model.srf_context_info),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Model.model_reference_type: %s\n",
                        name_ptr, SE_PrintModelReferenceType
                    (field_ptr->u.Model.model_reference_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Model.dynamic_model_processing: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Model.dynamic_model_processing));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Model.has_units: %s\n",name_ptr,
                        SE_PrintBoolean(field_ptr->u.Model.has_units));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Model.has_moving_parts: %s\n",name_ptr,
                        SE_PrintBoolean(field_ptr->u.Model.has_moving_parts));
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Model.name), "name", level);
                SE_PrintSRFContextInfo(&(field_ptr->u.Model.srf_context_info),
                  "srf_context_info", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "model_reference_type: %s\n",
                        SE_PrintModelReferenceType
                    (field_ptr->u.Model.model_reference_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "dynamic_model_processing: %s\n",SE_PrintBoolean
                    (field_ptr->u.Model.dynamic_model_processing));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "has_units: %s\n",SE_PrintBoolean
                    (field_ptr->u.Model.has_units));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "has_moving_parts: %s\n",SE_PrintBoolean
                    (field_ptr->u.Model.has_moving_parts));
            }
            break;

        case SE_CLS_DRM_MODEL_INSTANCE_TEMPLATE_INDEX:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Model_Instance_Template_Index.index:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Model_Instance_Template_Index.index));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "index: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Model_Instance_Template_Index.index));
            }
            break;

        case SE_CLS_DRM_MOVING_LIGHT_BEHAVIOUR:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Moving_Light_Behaviour.speed: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Moving_Light_Behaviour.speed));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Moving_Light_Behaviour.delay: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Moving_Light_Behaviour.delay));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "speed: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Moving_Light_Behaviour.speed));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delay: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Moving_Light_Behaviour.delay));
            }
            break;

        case SE_CLS_DRM_OCTANT_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Octant_Data.octant: %s\n",name_ptr,
                        SE_PrintOctant(field_ptr->u.Octant_Data.octant));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "octant: %s\n",SE_PrintOctant
                    (field_ptr->u.Octant_Data.octant));
            }
            break;

        case SE_CLS_DRM_OCTANT_RELATED_FEATURES:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Octant_Related_Features.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Octant_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Octant_Related_Features.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Octant_Related_Features.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Octant_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Octant_Related_Features.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_OCTANT_RELATED_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Octant_Related_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Octant_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Octant_Related_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Octant_Related_Geometry.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Octant_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Octant_Related_Geometry.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_OMS_AUGMENTED_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.OMS_Augmented_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintMapProjection3DCoordinate
                (&(field_ptr->u.OMS_Augmented_3D_Location.coordinate),
                  name_buffer, level);
            }
            else
            {
                SRM_PrintMapProjection3DCoordinate
                (&(field_ptr->u.OMS_Augmented_3D_Location.coordinate),
                  "coordinate", level);
            }
            break;

        case SE_CLS_DRM_OMS_SURFACE_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.OMS_Surface_Location.coordinate",
                        name_ptr);
                SRM_PrintMapProjectionSurfaceCoordinate
                (&(field_ptr->u.OMS_Surface_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintMapProjectionSurfaceCoordinate
                (&(field_ptr->u.OMS_Surface_Location.coordinate),
                  "coordinate", level);
            }
            break;

        case SE_CLS_DRM_OVERLOAD_PRIORITY_INDEX:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Overload_Priority_Index.overload_priority:"\
                        " %s\n", name_ptr, SE_PrintShortInteger
                        (field_ptr->u.Overload_Priority_Index.overload_priority));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "overload_priority: %s\n", SE_PrintShortInteger
                        (field_ptr->u.Overload_Priority_Index.overload_priority));
            }
            break;

        case SE_CLS_DRM_PARALLELEPIPED_VOLUME_EXTENT:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Parallelepiped_Volume_Extent.edge_length[0..2]: ", name_ptr);
                for (i = 0; i < 3; i++)
                {
                    fprintf(f_ptr, "%s ", SE_PrintLongFloat
                            (field_ptr->u.Parallelepiped_Volume_Extent.edge_length[i])
                            );
                } /* end for i */
                fprintf(f_ptr, "\n");
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "edge_length[0..2]: ");
                for (i = 0; i < 3; i++)
                {
                    fprintf(f_ptr, "%s ", SE_PrintLongFloat
                            (field_ptr->u.Parallelepiped_Volume_Extent.edge_length[i])
                            );
                } /* end for i */
                fprintf(f_ptr, "\n");
            }
            break;

        case SE_CLS_DRM_PD_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.PD_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintPD3DCoordinate
                (&(field_ptr->u.PD_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintPD3DCoordinate
                (&(field_ptr->u.PD_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_PD_SURFACE_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.PD_Surface_Location.coordinate",
                        name_ptr);
                SRM_PrintPDSurfaceCoordinate
                (&(field_ptr->u.PD_Surface_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintPDSurfaceCoordinate
                (&(field_ptr->u.PD_Surface_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_PERIMETER_RELATED_FEATURE_TOPOLOGY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Perimeter_Related_Feature_Topology.feature_topology_level:"\
                        " %s\n",name_ptr, SE_PrintFeatureTopologyLevel
                    (field_ptr->u.Perimeter_Related_Feature_Topology.feature_topology_level));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "feature_topology_level: %s\n",
                        SE_PrintFeatureTopologyLevel
                    (field_ptr->u.Perimeter_Related_Feature_Topology.feature_topology_level));
            }
            break;

        case SE_CLS_DRM_PERIMETER_RELATED_FEATURES:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Perimeter_Related_Features.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Perimeter_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Perimeter_Related_Features.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Perimeter_Related_Features.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Perimeter_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Perimeter_Related_Features.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_PERIMETER_RELATED_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Perimeter_Related_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Perimeter_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Perimeter_Related_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Perimeter_Related_Geometry.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Perimeter_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Perimeter_Related_Geometry.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_PERIMETER_RELATED_GEOMETRY_TOPOLOGY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Perimeter_Related_Geometry_Topology.geometry_topology_level:"\
                        " %s\n",name_ptr, SE_PrintGeometryTopologyLevel
                    (field_ptr->u.Perimeter_Related_Geometry_Topology.geometry_topology_level));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "geometry_topology_level: %s\n",
                        SE_PrintGeometryTopologyLevel
                    (field_ptr->u.Perimeter_Related_Geometry_Topology.geometry_topology_level));
            }
            break;

        case SE_CLS_DRM_POLYGON:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Polygon.polygon_flags", name_ptr);
                SE_PrintPolygonFlag(&(field_ptr->u.Polygon.polygon_flags),
                  name_buffer, level);
            }
            else
            {
                SE_PrintPolygonFlag(&(field_ptr->u.Polygon.polygon_flags),
                  "polygon_flags", level);
            }
            break;

        case SE_CLS_DRM_POLYGON_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Polygon_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Polygon_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Polygon_Control_Link.hat_test_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Polygon_Control_Link.hat_test_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Polygon_Control_Link.collidible_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Polygon_Control_Link.collidible_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Polygon_Control_Link.invisible_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Polygon_Control_Link.invisible_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Polygon_Control_Link.laser_range_finding_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Polygon_Control_Link.laser_range_finding_expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Polygon_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "hat_test_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Polygon_Control_Link.hat_test_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "collidible_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Polygon_Control_Link.collidible_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "invisible_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Polygon_Control_Link.invisible_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "laser_range_finding_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Polygon_Control_Link.laser_range_finding_expression_index));
            }
            break;

        case SE_CLS_DRM_POSITIONAL_LIGHT:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Positional_Light.apply_to_children:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Positional_Light.apply_to_children));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Positional_Light.override_positional_lights:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Positional_Light.override_positional_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Positional_Light.override_infinite_lights:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Positional_Light.override_infinite_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Positional_Light.active_light_value:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Positional_Light.active_light_value));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Positional_Light.radius: %s\n",
                        name_ptr, SE_PrintFloat
                        (field_ptr->u.Positional_Light.radius));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Positional_Light.constant_attenuation_factor:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Positional_Light.constant_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Positional_Light.linear_attenuation_factor:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Positional_Light.linear_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Positional_Light.quadratic_attenuation_factor:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Positional_Light.quadratic_attenuation_factor));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "apply_to_children: %s\n",SE_PrintBoolean
                    (field_ptr->u.Positional_Light.apply_to_children));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "override_positional_lights: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Positional_Light.override_positional_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "override_infinite_lights: %s\n",SE_PrintBoolean
                    (field_ptr->u.Positional_Light.override_infinite_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "active_light_value: %s\n",SE_PrintBoolean
                    (field_ptr->u.Positional_Light.active_light_value));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "radius: %s\n", SE_PrintFloat
                        (field_ptr->u.Positional_Light.radius));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "constant_attenuation_factor: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Positional_Light.constant_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "linear_attenuation_factor: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Positional_Light.linear_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "quadratic_attenuation_factor: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Positional_Light.quadratic_attenuation_factor));
            }
            break;

        case SE_CLS_DRM_PREDEFINED_FUNCTION:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Predefined_Function.value_type: %s\n",
                        name_ptr, EDCS_PrintAttributeValueType
                    (field_ptr->u.Predefined_Function.value_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Predefined_Function.function: %s\n",
                        name_ptr, SE_PrintPredefinedFunction
                    (field_ptr->u.Predefined_Function.function));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_type: %s\n",EDCS_PrintAttributeValueType
                    (field_ptr->u.Predefined_Function.value_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "function: %s\n",SE_PrintPredefinedFunction
                    (field_ptr->u.Predefined_Function.function));
            }
            break;

        case SE_CLS_DRM_PRESENTATION_DOMAIN:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Presentation_Domain.presentation_domain",
                        name_ptr);
                SE_PrintPresentationDomain
                (&(field_ptr->u.Presentation_Domain.presentation_domain),
                  name_buffer, level);
            }
            else
            {
                SE_PrintPresentationDomain
                (&(field_ptr->u.Presentation_Domain.presentation_domain),
                  "presentation_domain", level);
            }
            break;

        case SE_CLS_DRM_PRIMITIVE_SUMMARY_ITEM:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Primitive_Summary_Item.drm_class: %s\n",
                        name_ptr, SE_PrintDRMClass
                    (field_ptr->u.Primitive_Summary_Item.drm_class));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Primitive_Summary_Item.multiplicity:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Primitive_Summary_Item.multiplicity));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "drm_class: %s\n",SE_PrintDRMClass
                    (field_ptr->u.Primitive_Summary_Item.drm_class));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "multiplicity: %s\n", SE_PrintIntegerUnsigned
                        (field_ptr->u.Primitive_Summary_Item.multiplicity));
            }
            break;

        case SE_CLS_DRM_PROCESS_STEP:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Process_Step.description",
                        name_ptr);
                SE_PrintString(&(field_ptr->u.Process_Step.description),
                  name_buffer, level);
                sprintf(name_buffer,"%s->u.Process_Step.rationale", name_ptr);
                SE_PrintString(&(field_ptr->u.Process_Step.rationale),
                  name_buffer, level);
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Process_Step.description),
                  "description", level);
                SE_PrintString(&(field_ptr->u.Process_Step.rationale),
                  "rationale", level);
            }
            break;

        case SE_CLS_DRM_PROPERTY:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Property.meaning", name_ptr);
                SE_PrintPropertyCode(&(field_ptr->u.Property.meaning),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Property.apply_property_inheritance:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Property.apply_property_inheritance));
            }
            else
            {
                SE_PrintPropertyCode(&(field_ptr->u.Property.meaning),
                  "meaning", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "apply_property_inheritance: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Property.apply_property_inheritance));
            }
            break;

        case SE_CLS_DRM_PROPERTY_CHARACTERISTIC:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Property_Characteristic.meaning: %s\n",
                        name_ptr, EDCS_PrintValueCharacteristicCode
                    (field_ptr->u.Property_Characteristic.meaning));
                sprintf(name_buffer,
                        "%s->u.Property_Characteristic.characteristic_value",
                        name_ptr);
                EDCS_PrintAttributeValue(EAC_NULL,
                &(field_ptr->u.Property_Characteristic.characteristic_value),
                  name_buffer, level);
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "meaning: %s\n",
                        EDCS_PrintValueCharacteristicCode
                    (field_ptr->u.Property_Characteristic.meaning));
                EDCS_PrintAttributeValue(EAC_NULL,
                &(field_ptr->u.Property_Characteristic.characteristic_value),
                  "characteristic_value", level);
            }
            break;

        case SE_CLS_DRM_PROPERTY_DESCRIPTION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Property_Description.meaning",
                        name_ptr);
                SE_PrintPropertyCode
                (&(field_ptr->u.Property_Description.meaning), name_buffer,
                  level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Property_Description.apply_property_inheritance:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Property_Description.apply_property_inheritance));
            }
            else
            {
                SE_PrintPropertyCode
                (&(field_ptr->u.Property_Description.meaning), "meaning",
                  level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "apply_property_inheritance: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Property_Description.apply_property_inheritance));
            }
            break;

        case SE_CLS_DRM_PROPERTY_GRID:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Property_Grid.spatial_axes_count: %s\n",
                        name_ptr, SE_PrintShortIntegerPositive
                        (field_ptr->u.Property_Grid.spatial_axes_count));
                if ((field_ptr->u.Property_Grid.spatial_axes_count > 0) &&
                    (field_ptr->u.Property_Grid.location_index != NULL))
                {
                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Property_Grid.spatial_axes_count; i++)
                    {
                        SE_Indent(level, f_ptr);
                        fprintf(f_ptr, 
                                "%s->u.Property_Grid.location_index[%u]:"\
                                " %s\n", name_ptr, i, SE_PrintShortInteger
                                (field_ptr->u.Property_Grid.location_index[i]));
                    } /* end for i */
                }
                sprintf(name_buffer,"%s->u.Property_Grid.srf_context_info",
                        name_ptr);
                SE_PrintSRFContextInfo
                (&(field_ptr->u.Property_Grid.srf_context_info), name_buffer,
                  level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Property_Grid.data_present: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Property_Grid.data_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Property_Grid.relative_to_hook_point:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Property_Grid.relative_to_hook_point));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "spatial_axes_count: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Property_Grid.spatial_axes_count));
                if ((field_ptr->u.Property_Grid.spatial_axes_count > 0) &&
                    (field_ptr->u.Property_Grid.location_index != NULL))
                {
                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Property_Grid.spatial_axes_count; i++)
                    {
                        SE_Indent(level, f_ptr);
                        fprintf(f_ptr, "location_index[%u]: %s\n", i,
                                SE_PrintShortInteger
                                (field_ptr->u.Property_Grid.location_index[i]));
                    } /* end for i */
                }
                SE_PrintSRFContextInfo
                (&(field_ptr->u.Property_Grid.srf_context_info),
                  "srf_context_info", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "data_present: %s\n",SE_PrintBoolean
                    (field_ptr->u.Property_Grid.data_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "relative_to_hook_point: %s\n",SE_PrintBoolean
                    (field_ptr->u.Property_Grid.relative_to_hook_point));
            }
            break;

        case SE_CLS_DRM_PROPERTY_SET_INDEX:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Property_Set_Index.index: %s\n",
                        name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Property_Set_Index.index));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "index: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Property_Set_Index.index));
            }
            break;

        case SE_CLS_DRM_PROPERTY_SET_INDEX_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Property_Set_Index_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Property_Set_Index_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Property_Set_Index_Control_Link.expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Property_Set_Index_Control_Link.expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Property_Set_Index_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "expression_index: %s\n",
                        SE_PrintIntegerPositive
                        (field_ptr->u.Property_Set_Index_Control_Link.expression_index));
            }
            break;

        case SE_CLS_DRM_PROPERTY_SET_TABLE:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Property_Set_Table.table_usage",
                        name_ptr);
                SE_PrintString(&(field_ptr->u.Property_Set_Table.table_usage),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Property_Set_Table.regular: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Property_Set_Table.regular));
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Property_Set_Table.table_usage),
                  "table_usage", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "regular: %s\n",SE_PrintBoolean
                    (field_ptr->u.Property_Set_Table.regular));
            }
            break;

        case SE_CLS_DRM_PROPERTY_SET_TABLE_GROUP:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Property_Set_Table_Group.primary_table_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Property_Set_Table_Group.primary_table_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Property_Set_Table_Group.table_size:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Property_Set_Table_Group.table_size));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "primary_table_index: %s\n",
                        SE_PrintIntegerPositive
                        (field_ptr->u.Property_Set_Table_Group.primary_table_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "table_size: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Property_Set_Table_Group.table_size));
            }
            break;

        case SE_CLS_DRM_PROPERTY_TABLE_REFERENCE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Property_Table_Reference.axis_type:"\
                        " %s\n",name_ptr, EDCS_PrintAttributeCode
                    (field_ptr->u.Property_Table_Reference.axis_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Property_Table_Reference.index_on_axis:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Property_Table_Reference.index_on_axis));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis_type: %s\n",EDCS_PrintAttributeCode
                    (field_ptr->u.Property_Table_Reference.axis_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "index_on_axis: %s\n", SE_PrintIntegerUnsigned
                        (field_ptr->u.Property_Table_Reference.index_on_axis));
            }
            break;

        case SE_CLS_DRM_PROPERTY_TABLE_REFERENCE_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Property_Table_Reference_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Property_Table_Reference_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Property_Table_Reference_Control_Link.expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Property_Table_Reference_Control_Link.expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Property_Table_Reference_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "expression_index: %s\n",
                        SE_PrintIntegerPositive
                        (field_ptr->u.Property_Table_Reference_Control_Link.expression_index));
            }
            break;

        case SE_CLS_DRM_PROPERTY_VALUE:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Property_Value.meaning", name_ptr);
                SE_PrintPropertyCode(&(field_ptr->u.Property_Value.meaning),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Property_Value.apply_property_inheritance:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Property_Value.apply_property_inheritance));
                sprintf(name_buffer,"%s->u.Property_Value.value", name_ptr);
                EDCS_PrintAttributeValue
                (((field_ptr->u.Property_Value.meaning.code_type ==
                SE_PROPCODTYP_ATTRIBUTE) ?
                field_ptr->u.Property_Value.meaning.code.attribute :
                EAC_NULL), &(field_ptr->u.Property_Value.value), name_buffer,
                  level);
            }
            else
            {
                SE_PrintPropertyCode(&(field_ptr->u.Property_Value.meaning),
                  "meaning", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "apply_property_inheritance: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Property_Value.apply_property_inheritance));
                EDCS_PrintAttributeValue
                (((field_ptr->u.Property_Value.meaning.code_type ==
                SE_PROPCODTYP_ATTRIBUTE) ?
                field_ptr->u.Property_Value.meaning.code.attribute :
                EAC_NULL), &(field_ptr->u.Property_Value.value), "value",
                  level);
            }
            break;

        case SE_CLS_DRM_PROXIMITY_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Proximity_Data.meaning: %s\n",name_ptr,
                        SE_PrintSpatialAssociationMeaningType
                    (field_ptr->u.Proximity_Data.meaning));
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Proximity_Data.distance: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Proximity_Data.distance));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "meaning: %s\n",
                        SE_PrintSpatialAssociationMeaningType
                    (field_ptr->u.Proximity_Data.meaning));
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "distance: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Proximity_Data.distance));
            }
            break;

        case SE_CLS_DRM_PS_AUGMENTED_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.PS_Augmented_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintMapProjection3DCoordinate
                (&(field_ptr->u.PS_Augmented_3D_Location.coordinate),
                  name_buffer, level);
            }
            else
            {
                SRM_PrintMapProjection3DCoordinate
                (&(field_ptr->u.PS_Augmented_3D_Location.coordinate),
                  "coordinate", level);
            }
            break;

        case SE_CLS_DRM_PS_SURFACE_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.PS_Surface_Location.coordinate",
                        name_ptr);
                SRM_PrintMapProjectionSurfaceCoordinate
                (&(field_ptr->u.PS_Surface_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintMapProjectionSurfaceCoordinate
                (&(field_ptr->u.PS_Surface_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_PSEUDO_CODE_FUNCTION:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Pseudo_Code_Function.value_type: %s\n",
                        name_ptr, EDCS_PrintAttributeValueType
                    (field_ptr->u.Pseudo_Code_Function.value_type));
                sprintf(name_buffer,"%s->u.Pseudo_Code_Function.name",
                        name_ptr);
                SE_PrintString(&(field_ptr->u.Pseudo_Code_Function.name),
                  name_buffer, level);
                sprintf(name_buffer,"%s->u.Pseudo_Code_Function.pseudo_code",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Pseudo_Code_Function.pseudo_code),
                  name_buffer, level);
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_type: %s\n",EDCS_PrintAttributeValueType
                    (field_ptr->u.Pseudo_Code_Function.value_type));
                SE_PrintString(&(field_ptr->u.Pseudo_Code_Function.name),
                  "name", level);
                SE_PrintString
                (&(field_ptr->u.Pseudo_Code_Function.pseudo_code),
                  "pseudo_code", level);
            }
            break;

        case SE_CLS_DRM_PYRAMID_DIRECTIONAL_LIGHT:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Pyramid_Directional_Light.use_full_intensity:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Pyramid_Directional_Light.use_full_intensity));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Pyramid_Directional_Light.minimum_colour_intensity:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Pyramid_Directional_Light.minimum_colour_intensity));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Pyramid_Directional_Light.invisible_behind:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Pyramid_Directional_Light.invisible_behind));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "use_full_intensity: %s\n",SE_PrintBoolean
                    (field_ptr->u.Pyramid_Directional_Light.use_full_intensity));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "minimum_colour_intensity: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Pyramid_Directional_Light.minimum_colour_intensity));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "invisible_behind: %s\n",SE_PrintBoolean
                    (field_ptr->u.Pyramid_Directional_Light.invisible_behind));
            }
            break;

        case SE_CLS_DRM_QUADRANT_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Quadrant_Data.quadrant: %s\n",name_ptr,
                        SE_PrintQuadrant(field_ptr->u.Quadrant_Data.quadrant));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "quadrant: %s\n",SE_PrintQuadrant
                    (field_ptr->u.Quadrant_Data.quadrant));
            }
            break;

        case SE_CLS_DRM_QUADRANT_RELATED_FEATURES:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Quadrant_Related_Features.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Quadrant_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Quadrant_Related_Features.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Quadrant_Related_Features.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Quadrant_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Quadrant_Related_Features.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_QUADRANT_RELATED_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Quadrant_Related_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Quadrant_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Quadrant_Related_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Quadrant_Related_Geometry.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Quadrant_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Quadrant_Related_Geometry.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_REFERENCE_ORIGIN:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Reference_Origin.srf_context_info",
                        name_ptr);
                SE_PrintSRFContextInfo
                (&(field_ptr->u.Reference_Origin.srf_context_info),
                  name_buffer, level);
            }
            else
            {
                SE_PrintSRFContextInfo
                (&(field_ptr->u.Reference_Origin.srf_context_info),
                  "srf_context_info", level);
            }
            break;

        case SE_CLS_DRM_REFERENCE_SURFACE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Reference_Surface.classification: %s\n",
                        name_ptr, EDCS_PrintClassificationCode
                    (field_ptr->u.Reference_Surface.classification));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Reference_Surface.multiplicity_rule:"\
                        " %s\n",name_ptr,
                        SE_PrintReferenceSurfaceElevationSelect
                    (field_ptr->u.Reference_Surface.multiplicity_rule));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Reference_Surface.lod_rule: %s\n",
                        name_ptr, SE_PrintReferenceSurfaceLODSelect
                    (field_ptr->u.Reference_Surface.lod_rule));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "classification: %s\n",
                        EDCS_PrintClassificationCode
                    (field_ptr->u.Reference_Surface.classification));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "multiplicity_rule: %s\n",
                        SE_PrintReferenceSurfaceElevationSelect
                    (field_ptr->u.Reference_Surface.multiplicity_rule));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "lod_rule: %s\n",
                        SE_PrintReferenceSurfaceLODSelect
                    (field_ptr->u.Reference_Surface.lod_rule));
            }
            break;

        case SE_CLS_DRM_REFERENCE_VECTOR:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Reference_Vector.unit_vector: %s\n",
                        name_ptr, SRM_PrintVector3D
                        (field_ptr->u.Reference_Vector.unit_vector));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Reference_Vector.vector_type: %s\n",
                        name_ptr, SE_PrintReferenceVectorType
                    (field_ptr->u.Reference_Vector.vector_type));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unit_vector: %s\n", SRM_PrintVector3D
                        (field_ptr->u.Reference_Vector.unit_vector));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "vector_type: %s\n",SE_PrintReferenceVectorType
                    (field_ptr->u.Reference_Vector.vector_type));
            }
            break;

        case SE_CLS_DRM_REFERENCE_VECTOR_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Reference_Vector_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Reference_Vector_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Reference_Vector_Control_Link.v0_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Reference_Vector_Control_Link.v0_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Reference_Vector_Control_Link.v1_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Reference_Vector_Control_Link.v1_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Reference_Vector_Control_Link.v2_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Reference_Vector_Control_Link.v2_expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Reference_Vector_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "v0_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Reference_Vector_Control_Link.v0_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "v1_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Reference_Vector_Control_Link.v1_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "v2_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Reference_Vector_Control_Link.v2_expression_index));
            }
            break;

        case SE_CLS_DRM_REGULAR_AXIS:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Regular_Axis.axis_type: %s\n",name_ptr,
                        EDCS_PrintAttributeCode
                    (field_ptr->u.Regular_Axis.axis_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Regular_Axis.axis_value_count: %s\n",
                        name_ptr, SE_PrintShortIntegerPositive
                        (field_ptr->u.Regular_Axis.axis_value_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Regular_Axis.value_unit: %s\n",name_ptr,
                        EDCS_PrintUnitCode
                    (field_ptr->u.Regular_Axis.value_unit));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Regular_Axis.value_scale: %s\n",
                        name_ptr, EDCS_PrintUnitScaleCode
                    (field_ptr->u.Regular_Axis.value_scale));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Regular_Axis.interpolation_type: %s\n",
                        name_ptr, SE_PrintInterpolationType
                    (field_ptr->u.Regular_Axis.interpolation_type));
                sprintf(name_buffer,"%s->u.Regular_Axis.first_value",
                        name_ptr);
                SE_PrintSingleValue(field_ptr->u.Regular_Axis.axis_type,
                &(field_ptr->u.Regular_Axis.first_value), name_buffer, level);
                sprintf(name_buffer,"%s->u.Regular_Axis.spacing", name_ptr);
                SE_PrintSingleValue(field_ptr->u.Regular_Axis.axis_type,
                &(field_ptr->u.Regular_Axis.spacing), name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Regular_Axis.spacing_type: %s\n",
                        name_ptr, SE_PrintSpacingType
                    (field_ptr->u.Regular_Axis.spacing_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Regular_Axis.axis_alignment: %s\n",
                        name_ptr, SE_PrintAxisAlignment
                    (field_ptr->u.Regular_Axis.axis_alignment));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis_type: %s\n",EDCS_PrintAttributeCode
                    (field_ptr->u.Regular_Axis.axis_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis_value_count: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Regular_Axis.axis_value_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_unit: %s\n",EDCS_PrintUnitCode
                    (field_ptr->u.Regular_Axis.value_unit));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_scale: %s\n",EDCS_PrintUnitScaleCode
                    (field_ptr->u.Regular_Axis.value_scale));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "interpolation_type: %s\n",
                        SE_PrintInterpolationType
                    (field_ptr->u.Regular_Axis.interpolation_type));
                SE_PrintSingleValue(field_ptr->u.Regular_Axis.axis_type,
                &(field_ptr->u.Regular_Axis.first_value), "first_value",
                  level);
                SE_PrintSingleValue(field_ptr->u.Regular_Axis.axis_type,
                &(field_ptr->u.Regular_Axis.spacing), "spacing", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "spacing_type: %s\n",SE_PrintSpacingType
                    (field_ptr->u.Regular_Axis.spacing_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis_alignment: %s\n",SE_PrintAxisAlignment
                    (field_ptr->u.Regular_Axis.axis_alignment));
            }
            break;

        case SE_CLS_DRM_RELATIVE_TIME:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Relative_Time.time_significance: %s\n",
                        name_ptr, SE_PrintTimeSignificance
                    (field_ptr->u.Relative_Time.time_significance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Relative_Time.delta_days: %s\n",
                        name_ptr, SE_PrintInteger
                        (field_ptr->u.Relative_Time.delta_days));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Relative_Time.delta_hours: %s\n",
                        name_ptr, SE_PrintByteUnsigned
                        (field_ptr->u.Relative_Time.delta_hours));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Relative_Time.delta_minutes: %s\n",
                        name_ptr, SE_PrintByteUnsigned
                        (field_ptr->u.Relative_Time.delta_minutes));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Relative_Time.delta_seconds: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Relative_Time.delta_seconds));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "time_significance: %s\n",
                        SE_PrintTimeSignificance
                    (field_ptr->u.Relative_Time.time_significance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_days: %s\n", SE_PrintInteger
                        (field_ptr->u.Relative_Time.delta_days));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_hours: %s\n", SE_PrintByteUnsigned
                        (field_ptr->u.Relative_Time.delta_hours));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_minutes: %s\n", SE_PrintByteUnsigned
                        (field_ptr->u.Relative_Time.delta_minutes));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_seconds: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Relative_Time.delta_seconds));
            }
            break;

        case SE_CLS_DRM_RELATIVE_TIME_INTERVAL:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Relative_Time_Interval.time_significance:"\
                        " %s\n",name_ptr, SE_PrintTimeSignificance
                    (field_ptr->u.Relative_Time_Interval.time_significance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Relative_Time_Interval.delta_start_days:"\
                        " %s\n", name_ptr, SE_PrintInteger
                        (field_ptr->u.Relative_Time_Interval.delta_start_days));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Relative_Time_Interval.delta_stop_days:"\
                        " %s\n", name_ptr, SE_PrintInteger
                        (field_ptr->u.Relative_Time_Interval.delta_stop_days));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Relative_Time_Interval.delta_start_hours:"\
                        " %s\n", name_ptr, SE_PrintByteUnsigned
                        (field_ptr->u.Relative_Time_Interval.delta_start_hours));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Relative_Time_Interval.delta_stop_hours:"\
                        " %s\n", name_ptr, SE_PrintByteUnsigned
                        (field_ptr->u.Relative_Time_Interval.delta_stop_hours));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Relative_Time_Interval.delta_start_minutes:"\
                        " %s\n", name_ptr, SE_PrintByteUnsigned
                        (field_ptr->u.Relative_Time_Interval.delta_start_minutes));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Relative_Time_Interval.delta_stop_minutes:"\
                        " %s\n", name_ptr, SE_PrintByteUnsigned
                        (field_ptr->u.Relative_Time_Interval.delta_stop_minutes));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Relative_Time_Interval.delta_start_seconds:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Relative_Time_Interval.delta_start_seconds));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Relative_Time_Interval.delta_stop_seconds:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Relative_Time_Interval.delta_stop_seconds));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "time_significance: %s\n",
                        SE_PrintTimeSignificance
                    (field_ptr->u.Relative_Time_Interval.time_significance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_start_days: %s\n", SE_PrintInteger
                        (field_ptr->u.Relative_Time_Interval.delta_start_days));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_stop_days: %s\n", SE_PrintInteger
                        (field_ptr->u.Relative_Time_Interval.delta_stop_days));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_start_hours: %s\n", SE_PrintByteUnsigned
                        (field_ptr->u.Relative_Time_Interval.delta_start_hours));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_stop_hours: %s\n", SE_PrintByteUnsigned
                        (field_ptr->u.Relative_Time_Interval.delta_stop_hours));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_start_minutes: %s\n",
                        SE_PrintByteUnsigned
                        (field_ptr->u.Relative_Time_Interval.delta_start_minutes));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_stop_minutes: %s\n", SE_PrintByteUnsigned
                        (field_ptr->u.Relative_Time_Interval.delta_stop_minutes));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_start_seconds: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Relative_Time_Interval.delta_start_seconds));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delta_stop_seconds: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Relative_Time_Interval.delta_stop_seconds));
            }
            break;

        case SE_CLS_DRM_RENDERING_PRIORITY_LEVEL:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Rendering_Priority_Level.rendering_group:"\
                        " %s\n", name_ptr, SE_PrintShortIntegerPositive
                        (field_ptr->u.Rendering_Priority_Level.rendering_group));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Rendering_Priority_Level.rendering_priority:"\
                        " %s\n", name_ptr, SE_PrintShortInteger
                        (field_ptr->u.Rendering_Priority_Level.rendering_priority));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "rendering_group: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Rendering_Priority_Level.rendering_group));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "rendering_priority: %s\n", SE_PrintShortInteger
                        (field_ptr->u.Rendering_Priority_Level.rendering_priority));
            }
            break;

        case SE_CLS_DRM_RENDERING_PROPERTIES:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Rendering_Properties.fill_method: %s\n",
                        name_ptr, SE_PrintPixelFillMethod
                    (field_ptr->u.Rendering_Properties.fill_method));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Rendering_Properties.shading_method:"\
                        " %s\n",name_ptr, SE_PrintShadingMethod
                    (field_ptr->u.Rendering_Properties.shading_method));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Rendering_Properties.colour_binding:"\
                        " %s\n",name_ptr, SE_PrintColourBinding
                    (field_ptr->u.Rendering_Properties.colour_binding));
                sprintf(name_buffer,"%s->u.Rendering_Properties.style",
                        name_ptr);
                SE_PrintDisplayStyle
                (&(field_ptr->u.Rendering_Properties.style), name_buffer,
                  level);
                sprintf(name_buffer,"%s->u.Rendering_Properties.side",
                        name_ptr);
                SE_PrintDisplaySide(&(field_ptr->u.Rendering_Properties.side),
                  name_buffer, level);
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "fill_method: %s\n",SE_PrintPixelFillMethod
                    (field_ptr->u.Rendering_Properties.fill_method));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "shading_method: %s\n",SE_PrintShadingMethod
                    (field_ptr->u.Rendering_Properties.shading_method));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "colour_binding: %s\n",SE_PrintColourBinding
                    (field_ptr->u.Rendering_Properties.colour_binding));
                SE_PrintDisplayStyle
                (&(field_ptr->u.Rendering_Properties.style), "style", level);
                SE_PrintDisplaySide(&(field_ptr->u.Rendering_Properties.side),
                  "side", level);
            }
            break;

        case SE_CLS_DRM_RESPONSIBLE_PARTY:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Responsible_Party.individual_name",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Responsible_Party.individual_name),
                  name_buffer, level);
                sprintf(name_buffer,
                        "%s->u.Responsible_Party.organization_name",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Responsible_Party.organization_name),
                  name_buffer, level);
                sprintf(name_buffer,"%s->u.Responsible_Party.position_name",
                        name_ptr);
                SE_PrintString(&(field_ptr->u.Responsible_Party.position_name),
                  name_buffer, level);
                sprintf(name_buffer,
                        "%s->u.Responsible_Party.contact_information",
                        name_ptr);
                SE_PrintContactInformation
                (&(field_ptr->u.Responsible_Party.contact_information),
                  name_buffer, level);
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Responsible_Party.individual_name),
                  "individual_name", level);
                SE_PrintString
                (&(field_ptr->u.Responsible_Party.organization_name),
                  "organization_name", level);
                SE_PrintString(&(field_ptr->u.Responsible_Party.position_name),
                  "position_name", level);
                SE_PrintContactInformation
                (&(field_ptr->u.Responsible_Party.contact_information),
                  "contact_information", level);
            }
            break;

        case SE_CLS_DRM_RGB_COLOUR:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.RGB_Colour.rgb_data", name_ptr);
                SE_PrintRGBData(&(field_ptr->u.RGB_Colour.rgb_data),
                  name_buffer, level);
            }
            else
            {
                SE_PrintRGBData(&(field_ptr->u.RGB_Colour.rgb_data),
                  "rgb_data", level);
            }
            break;

        case SE_CLS_DRM_RGB_COLOUR_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.RGB_Colour_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.RGB_Colour_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.RGB_Colour_Control_Link.red_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.RGB_Colour_Control_Link.red_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.RGB_Colour_Control_Link.green_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.RGB_Colour_Control_Link.green_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.RGB_Colour_Control_Link.blue_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.RGB_Colour_Control_Link.blue_expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.RGB_Colour_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "red_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.RGB_Colour_Control_Link.red_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "green_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.RGB_Colour_Control_Link.green_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "blue_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.RGB_Colour_Control_Link.blue_expression_index));
            }
            break;

        case SE_CLS_DRM_ROLE_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Role_Data.role: %s\n",name_ptr,
                        SE_PrintCIRoleCode(field_ptr->u.Role_Data.role));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "role: %s\n",SE_PrintCIRoleCode
                    (field_ptr->u.Role_Data.role));
            }
            break;

        case SE_CLS_DRM_ROTATING_LIGHT_BEHAVIOUR:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Rotating_Light_Behaviour.period: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Rotating_Light_Behaviour.period));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "period: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Rotating_Light_Behaviour.period));
            }
            break;

        case SE_CLS_DRM_ROTATION:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Rotation.axis: %s\n",name_ptr,
                        SE_PrintLSRTransformationAxis
                    (field_ptr->u.Rotation.axis));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Rotation.angle: %s\n", name_ptr,
                        SE_PrintLongFloat(field_ptr->u.Rotation.angle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis: %s\n",SE_PrintLSRTransformationAxis
                    (field_ptr->u.Rotation.axis));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "angle: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Rotation.angle));
            }
            break;

        case SE_CLS_DRM_ROTATION_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Rotation_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Rotation_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Rotation_Control_Link.expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Rotation_Control_Link.expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Rotation_Control_Link.lower_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Rotation_Control_Link.lower_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Rotation_Control_Link.upper_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Rotation_Control_Link.upper_expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Rotation_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "expression_index: %s\n",
                        SE_PrintIntegerPositive
                        (field_ptr->u.Rotation_Control_Link.expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "lower_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Rotation_Control_Link.lower_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "upper_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Rotation_Control_Link.upper_expression_index));
            }
            break;

        case SE_CLS_DRM_SCALE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Scale.axis: %s\n",name_ptr,
                        SE_PrintLSRTransformationAxis
                    (field_ptr->u.Scale.axis));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Scale.scale_factor: %s\n", name_ptr,
                        SE_PrintLongFloat(field_ptr->u.Scale.scale_factor));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis: %s\n",SE_PrintLSRTransformationAxis
                    (field_ptr->u.Scale.axis));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "scale_factor: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Scale.scale_factor));
            }
            break;

        case SE_CLS_DRM_SCALE_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Scale_Control_Link.description",
                        name_ptr);
                SE_PrintString(&(field_ptr->u.Scale_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Scale_Control_Link.expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Scale_Control_Link.expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Scale_Control_Link.lower_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Scale_Control_Link.lower_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Scale_Control_Link.upper_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Scale_Control_Link.upper_expression_index));
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Scale_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "expression_index: %s\n",
                        SE_PrintIntegerPositive
                        (field_ptr->u.Scale_Control_Link.expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "lower_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Scale_Control_Link.lower_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "upper_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Scale_Control_Link.upper_expression_index));
            }
            break;

        case SE_CLS_DRM_SEASON:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Season.time_significance: %s\n",
                        name_ptr, SE_PrintTimeSignificance
                    (field_ptr->u.Season.time_significance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Season.season: %s\n",name_ptr,
                        SE_PrintSeason(field_ptr->u.Season.season));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "time_significance: %s\n",
                        SE_PrintTimeSignificance
                    (field_ptr->u.Season.time_significance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "season: %s\n",SE_PrintSeason
                    (field_ptr->u.Season.season));
            }
            break;

        case SE_CLS_DRM_SECURITY_CONSTRAINTS:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Security_Constraints.use_limitation_count:"\
                        " %s\n", name_ptr, SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Security_Constraints.use_limitation_count));
                if ((field_ptr->u.Security_Constraints.use_limitation_count >
                    0) && (field_ptr->u.Security_Constraints.use_limitation !=
                    NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Security_Constraints.use_limitation_count;
                        i++)
                    {
                        sprintf(buffer, "%s->u.Security_Constraints.use_limitation[%u]", name_ptr, i);
                        SE_PrintString
                           (&(field_ptr->u.Security_Constraints.use_limitation[i]),
                           buffer, level);
                    } /* end for i */
                }
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Security_Constraints.classification:"\
                        " %s\n",name_ptr, SE_PrintMDClassificationCode
                    (field_ptr->u.Security_Constraints.classification));
                sprintf(name_buffer,"%s->u.Security_Constraints.user_note",
                        name_ptr);
                SE_PrintString(&(field_ptr->u.Security_Constraints.user_note),
                  name_buffer, level);
                sprintf(name_buffer,
                        "%s->u.Security_Constraints.classification_system",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Security_Constraints.classification_system),
                  name_buffer, level);
                sprintf(name_buffer,
                        "%s->u.Security_Constraints.handling_description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Security_Constraints.handling_description),
                  name_buffer, level);
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "use_limitation_count: %s\n",
                        SE_PrintShortIntegerUnsigned
                        (field_ptr->u.Security_Constraints.use_limitation_count));
                if ((field_ptr->u.Security_Constraints.use_limitation_count >
                    0) && (field_ptr->u.Security_Constraints.use_limitation !=
                    NULL))
                {
                    char buffer[1024];

                    for (i = 0; i < (SE_Integer_Unsigned)
                        field_ptr->u.Security_Constraints.use_limitation_count;
                        i++)
                    {
                        sprintf(buffer, "use_limitation[%u]", i);
                        SE_PrintString
                           (&(field_ptr->u.Security_Constraints.use_limitation[i]),
                           buffer, level);
                    } /* end for i */
                }
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "classification: %s\n",
                        SE_PrintMDClassificationCode
                    (field_ptr->u.Security_Constraints.classification));
                SE_PrintString(&(field_ptr->u.Security_Constraints.user_note),
                  "user_note", level);
                SE_PrintString
                (&(field_ptr->u.Security_Constraints.classification_system),
                  "classification_system", level);
                SE_PrintString
                (&(field_ptr->u.Security_Constraints.handling_description),
                  "handling_description", level);
            }
            break;

        case SE_CLS_DRM_SEC_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.SEC_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.SEC_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.SEC_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_SEPARATING_PLANE_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Separating_Plane_Data.positive: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Separating_Plane_Data.positive));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "positive: %s\n",SE_PrintBoolean
                    (field_ptr->u.Separating_Plane_Data.positive));
            }
            break;

        case SE_CLS_DRM_SEPARATING_PLANE_RELATED_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Separating_Plane_Related_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Separating_Plane_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Separating_Plane_Related_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Separating_Plane_Related_Geometry.strict_organizing_principle));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Separating_Plane_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Separating_Plane_Related_Geometry.strict_organizing_principle));
            }
            break;

        case SE_CLS_DRM_SEQ_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.SEQ_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.SEQ_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.SEQ_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_SMD_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.SMD_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.SMD_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.SMD_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_SME_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.SME_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.SME_3D_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintSpherical3DCoordinate
                (&(field_ptr->u.SME_3D_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_SOUND:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Sound.name", name_ptr);
                SE_PrintString(&(field_ptr->u.Sound.name), name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Sound.sound_format: %s\n",name_ptr,
                        SE_PrintSoundFormat(field_ptr->u.Sound.sound_format));
                sprintf(name_buffer,"%s->u.Sound.sound_urn", name_ptr);
                SE_PrintURN(&(field_ptr->u.Sound.sound_urn), name_buffer,
                  level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Sound.duration: %s\n", name_ptr,
                        SE_PrintFloat(field_ptr->u.Sound.duration));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Sound.sampling_rate: %s\n", name_ptr,
                        SE_PrintFloat(field_ptr->u.Sound.sampling_rate));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Sound.bits_per_sample: %s\n", name_ptr,
                        SE_PrintBytePositive
                        (field_ptr->u.Sound.bits_per_sample));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Sound.channel_count: %s\n", name_ptr,
                        SE_PrintBytePositive
                        (field_ptr->u.Sound.channel_count));
                sprintf(name_buffer,"%s->u.Sound.method", name_ptr);
                SE_PrintString(&(field_ptr->u.Sound.method), name_buffer,
                  level);
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Sound.name), "name", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "sound_format: %s\n",SE_PrintSoundFormat
                    (field_ptr->u.Sound.sound_format));
                SE_PrintURN(&(field_ptr->u.Sound.sound_urn), "sound_urn",
                  level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "duration: %s\n", SE_PrintFloat
                        (field_ptr->u.Sound.duration));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "sampling_rate: %s\n", SE_PrintFloat
                        (field_ptr->u.Sound.sampling_rate));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "bits_per_sample: %s\n", SE_PrintBytePositive
                        (field_ptr->u.Sound.bits_per_sample));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "channel_count: %s\n", SE_PrintBytePositive
                        (field_ptr->u.Sound.channel_count));
                SE_PrintString(&(field_ptr->u.Sound.method), "method", level);
            }
            break;

        case SE_CLS_DRM_SOUND_INSTANCE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Sound_Instance.active_sound_value: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Sound_Instance.active_sound_value));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "active_sound_value: %s\n",SE_PrintBoolean
                    (field_ptr->u.Sound_Instance.active_sound_value));
            }
            break;

        case SE_CLS_DRM_SOUND_INSTANCE_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Sound_Instance_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Sound_Instance_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Sound_Instance_Control_Link.active_sound_value_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Sound_Instance_Control_Link.active_sound_value_expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Sound_Instance_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "active_sound_value_expression_index: %s\n",
                        SE_PrintIntegerPositive
                        (field_ptr->u.Sound_Instance_Control_Link.active_sound_value_expression_index));
            }
            break;

        case SE_CLS_DRM_SOURCE:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Source.description", name_ptr);
                SE_PrintString(&(field_ptr->u.Source.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Source.scale: %s\n", name_ptr,
                        SE_PrintIntegerPositive(field_ptr->u.Source.scale));
                sprintf(name_buffer,"%s->u.Source.contribution", name_ptr);
                SE_PrintString(&(field_ptr->u.Source.contribution),
                  name_buffer, level);
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Source.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "scale: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Source.scale));
                SE_PrintString(&(field_ptr->u.Source.contribution),
                  "contribution", level);
            }
            break;

        case SE_CLS_DRM_SPATIAL_ASSOCIATION_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spatial_Association_Data.meaning: %s\n",
                        name_ptr, SE_PrintSpatialAssociationMeaningType
                    (field_ptr->u.Spatial_Association_Data.meaning));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "meaning: %s\n",
                        SE_PrintSpatialAssociationMeaningType
                    (field_ptr->u.Spatial_Association_Data.meaning));
            }
            break;

        case SE_CLS_DRM_SPATIAL_INDEX_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spatial_Index_Data.row_index: %s\n",
                        name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Data.row_index));
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spatial_Index_Data.column_index: %s\n",
                        name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Data.column_index));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "row_index: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Data.row_index));
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "column_index: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Data.column_index));
            }
            break;

        case SE_CLS_DRM_SPATIAL_INDEX_RELATED_FEATURE_TOPOLOGY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Feature_Topology.feature_topology_level:"\
                        " %s\n",name_ptr, SE_PrintFeatureTopologyLevel
                    (field_ptr->u.Spatial_Index_Related_Feature_Topology.feature_topology_level));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Feature_Topology.sparse:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Feature_Topology.sparse));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Feature_Topology.column_count:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Feature_Topology.column_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Feature_Topology.row_count:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Feature_Topology.row_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Feature_Topology.column_width:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Feature_Topology.column_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Feature_Topology.row_width:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Feature_Topology.row_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Feature_Topology.spacing_unit:"\
                        " %s\n",name_ptr, SE_PrintSpatialIndexSpacingUnit
                    (field_ptr->u.Spatial_Index_Related_Feature_Topology.spacing_unit));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "feature_topology_level: %s\n",
                        SE_PrintFeatureTopologyLevel
                    (field_ptr->u.Spatial_Index_Related_Feature_Topology.feature_topology_level));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "sparse: %s\n",SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Feature_Topology.sparse));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "column_count: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Feature_Topology.column_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "row_count: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Feature_Topology.row_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "column_width: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Feature_Topology.column_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "row_width: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Feature_Topology.row_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "spacing_unit: %s\n",
                        SE_PrintSpatialIndexSpacingUnit
                    (field_ptr->u.Spatial_Index_Related_Feature_Topology.spacing_unit));
            }
            break;

        case SE_CLS_DRM_SPATIAL_INDEX_RELATED_FEATURES:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Features.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Features.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Features.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spatial_Index_Related_Features.sparse:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Features.sparse));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Features.column_count:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Features.column_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Features.row_count:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Features.row_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Features.column_width:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Features.column_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Features.row_width:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Features.row_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Features.spacing_unit:"\
                        " %s\n",name_ptr, SE_PrintSpatialIndexSpacingUnit
                    (field_ptr->u.Spatial_Index_Related_Features.spacing_unit));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Features.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "sparse: %s\n",SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Features.sparse));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "column_count: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Features.column_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "row_count: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Features.row_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "column_width: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Features.column_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "row_width: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Features.row_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "spacing_unit: %s\n",
                        SE_PrintSpatialIndexSpacingUnit
                    (field_ptr->u.Spatial_Index_Related_Features.spacing_unit));
            }
            break;

        case SE_CLS_DRM_SPATIAL_INDEX_RELATED_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spatial_Index_Related_Geometry.sparse:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Geometry.sparse));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry.column_count:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Geometry.column_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry.row_count:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Geometry.row_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry.column_width:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Geometry.column_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry.row_width:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Geometry.row_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry.spacing_unit:"\
                        " %s\n",name_ptr, SE_PrintSpatialIndexSpacingUnit
                    (field_ptr->u.Spatial_Index_Related_Geometry.spacing_unit));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "sparse: %s\n",SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Geometry.sparse));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "column_count: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Geometry.column_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "row_count: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Geometry.row_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "column_width: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Geometry.column_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "row_width: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Geometry.row_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "spacing_unit: %s\n",
                        SE_PrintSpatialIndexSpacingUnit
                    (field_ptr->u.Spatial_Index_Related_Geometry.spacing_unit));
            }
            break;

        case SE_CLS_DRM_SPATIAL_INDEX_RELATED_GEOMETRY_TOPOLOGY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry_Topology.geometry_topology_level:"\
                        " %s\n",name_ptr, SE_PrintGeometryTopologyLevel
                    (field_ptr->u.Spatial_Index_Related_Geometry_Topology.geometry_topology_level));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry_Topology.sparse:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Geometry_Topology.sparse));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry_Topology.column_count:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Geometry_Topology.column_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry_Topology.row_count:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Geometry_Topology.row_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry_Topology.column_width:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Geometry_Topology.column_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry_Topology.row_width:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Geometry_Topology.row_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Index_Related_Geometry_Topology.spacing_unit:"\
                        " %s\n",name_ptr, SE_PrintSpatialIndexSpacingUnit
                    (field_ptr->u.Spatial_Index_Related_Geometry_Topology.spacing_unit));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "geometry_topology_level: %s\n",
                        SE_PrintGeometryTopologyLevel
                    (field_ptr->u.Spatial_Index_Related_Geometry_Topology.geometry_topology_level));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "sparse: %s\n",SE_PrintBoolean
                    (field_ptr->u.Spatial_Index_Related_Geometry_Topology.sparse));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "column_count: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Geometry_Topology.column_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "row_count: %s\n", SE_PrintIntegerPositive
                        (field_ptr->u.Spatial_Index_Related_Geometry_Topology.row_count));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "column_width: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Geometry_Topology.column_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "row_width: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Spatial_Index_Related_Geometry_Topology.row_width));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "spacing_unit: %s\n",
                        SE_PrintSpatialIndexSpacingUnit
                    (field_ptr->u.Spatial_Index_Related_Geometry_Topology.spacing_unit));
            }
            break;

        case SE_CLS_DRM_SPATIAL_RESOLUTION_LOD_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spatial_Resolution_LOD_Data.spatial_resolution:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spatial_Resolution_LOD_Data.spatial_resolution));
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spatial_Resolution_LOD_Data.unit: %s\n",
                        name_ptr, SE_PrintSpatialIndexSpacingUnit
                    (field_ptr->u.Spatial_Resolution_LOD_Data.unit));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "spatial_resolution: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Spatial_Resolution_LOD_Data.spatial_resolution));
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "unit: %s\n",SE_PrintSpatialIndexSpacingUnit
                    (field_ptr->u.Spatial_Resolution_LOD_Data.unit));
            }
            break;

        case SE_CLS_DRM_SPHERICAL_VOLUME_EXTENT:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spherical_Volume_Extent.radius: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spherical_Volume_Extent.radius));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "radius: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Spherical_Volume_Extent.radius));
            }
            break;

        case SE_CLS_DRM_SPOT_LIGHT:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spot_Light.apply_to_children: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Spot_Light.apply_to_children));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spot_Light.override_positional_lights:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Spot_Light.override_positional_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spot_Light.override_infinite_lights:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Spot_Light.override_infinite_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spot_Light.active_light_value: %s\n",
                        name_ptr, SE_PrintBoolean
                    (field_ptr->u.Spot_Light.active_light_value));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spot_Light.radius: %s\n", name_ptr,
                        SE_PrintFloat(field_ptr->u.Spot_Light.radius));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spot_Light.constant_attenuation_factor:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spot_Light.constant_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spot_Light.linear_attenuation_factor:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spot_Light.linear_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Spot_Light.quadratic_attenuation_factor:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spot_Light.quadratic_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spot_Light.horizontal_drop_off_rate:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spot_Light.horizontal_drop_off_rate));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Spot_Light.vertical_drop_off_rate: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Spot_Light.vertical_drop_off_rate));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "apply_to_children: %s\n",SE_PrintBoolean
                    (field_ptr->u.Spot_Light.apply_to_children));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "override_positional_lights: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Spot_Light.override_positional_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "override_infinite_lights: %s\n",SE_PrintBoolean
                    (field_ptr->u.Spot_Light.override_infinite_lights));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "active_light_value: %s\n",SE_PrintBoolean
                    (field_ptr->u.Spot_Light.active_light_value));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "radius: %s\n", SE_PrintFloat
                        (field_ptr->u.Spot_Light.radius));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "constant_attenuation_factor: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Spot_Light.constant_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "linear_attenuation_factor: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Spot_Light.linear_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "quadratic_attenuation_factor: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Spot_Light.quadratic_attenuation_factor));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "horizontal_drop_off_rate: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Spot_Light.horizontal_drop_off_rate));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "vertical_drop_off_rate: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Spot_Light.vertical_drop_off_rate));
            }
            break;

        case SE_CLS_DRM_SRF_SUMMARY:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.SRF_Summary.srf_context_info",
                        name_ptr);
                SE_PrintSRFContextInfo
                (&(field_ptr->u.SRF_Summary.srf_context_info), name_buffer,
                  level);
            }
            else
            {
                SE_PrintSRFContextInfo
                (&(field_ptr->u.SRF_Summary.srf_context_info),
                  "srf_context_info", level);
            }
            break;

        case SE_CLS_DRM_STAMP_BEHAVIOUR:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Stamp_Behaviour.u_axis_limits",
                        name_ptr);
                SE_PrintRotationData
                (&(field_ptr->u.Stamp_Behaviour.u_axis_limits), name_buffer,
                  level);
                sprintf(name_buffer,"%s->u.Stamp_Behaviour.v_axis_limits",
                        name_ptr);
                SE_PrintRotationData
                (&(field_ptr->u.Stamp_Behaviour.v_axis_limits), name_buffer,
                  level);
                sprintf(name_buffer,"%s->u.Stamp_Behaviour.w_axis_limits",
                        name_ptr);
                SE_PrintRotationData
                (&(field_ptr->u.Stamp_Behaviour.w_axis_limits), name_buffer,
                  level);
            }
            else
            {
                SE_PrintRotationData
                (&(field_ptr->u.Stamp_Behaviour.u_axis_limits),
                  "u_axis_limits", level);
                SE_PrintRotationData
                (&(field_ptr->u.Stamp_Behaviour.v_axis_limits),
                  "v_axis_limits", level);
                SE_PrintRotationData
                (&(field_ptr->u.Stamp_Behaviour.w_axis_limits),
                  "w_axis_limits", level);
            }
            break;

        case SE_CLS_DRM_STATE_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.State_Control_Link.description",
                        name_ptr);
                SE_PrintString(&(field_ptr->u.State_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.State_Control_Link.expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.State_Control_Link.expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.State_Control_Link.mismatch_behaviour:"\
                        " %s\n",name_ptr, SE_PrintStateMismatchBehaviour
                    (field_ptr->u.State_Control_Link.mismatch_behaviour));
            }
            else
            {
                SE_PrintString(&(field_ptr->u.State_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "expression_index: %s\n",
                        SE_PrintIntegerPositive
                        (field_ptr->u.State_Control_Link.expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "mismatch_behaviour: %s\n",
                        SE_PrintStateMismatchBehaviour
                    (field_ptr->u.State_Control_Link.mismatch_behaviour));
            }
            break;

        case SE_CLS_DRM_STATE_DATA:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.State_Data.state_value", name_ptr);
                EDCS_PrintAttributeValue(EAC_NULL,
                &(field_ptr->u.State_Data.state_value), name_buffer, level);
            }
            else
            {
                EDCS_PrintAttributeValue(EAC_NULL,
                &(field_ptr->u.State_Data.state_value), "state_value", level);
            }
            break;

        case SE_CLS_DRM_STATE_RELATED_FEATURES:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.State_Related_Features.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.State_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.State_Related_Features.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.State_Related_Features.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.State_Related_Features.state_tag: %s\n",
                        name_ptr, EDCS_PrintAttributeCode
                    (field_ptr->u.State_Related_Features.state_tag));
                sprintf(name_buffer,
                        "%s->u.State_Related_Features.active_state_value",
                        name_ptr);
                EDCS_PrintAttributeValue(
                field_ptr->u.State_Related_Features.state_tag,
                &(field_ptr->u.State_Related_Features.active_state_value),
                  name_buffer, level);
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.State_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.State_Related_Features.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "state_tag: %s\n",EDCS_PrintAttributeCode
                    (field_ptr->u.State_Related_Features.state_tag));
                EDCS_PrintAttributeValue(
                field_ptr->u.State_Related_Features.state_tag,
                &(field_ptr->u.State_Related_Features.active_state_value),
                  "active_state_value", level);
            }
            break;

        case SE_CLS_DRM_STATE_RELATED_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.State_Related_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.State_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.State_Related_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.State_Related_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.State_Related_Geometry.state_tag: %s\n",
                        name_ptr, EDCS_PrintAttributeCode
                    (field_ptr->u.State_Related_Geometry.state_tag));
                sprintf(name_buffer,
                        "%s->u.State_Related_Geometry.active_state_value",
                        name_ptr);
                EDCS_PrintAttributeValue(
                field_ptr->u.State_Related_Geometry.state_tag,
                &(field_ptr->u.State_Related_Geometry.active_state_value),
                  name_buffer, level);
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.State_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.State_Related_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "state_tag: %s\n",EDCS_PrintAttributeCode
                    (field_ptr->u.State_Related_Geometry.state_tag));
                EDCS_PrintAttributeValue(
                field_ptr->u.State_Related_Geometry.state_tag,
                &(field_ptr->u.State_Related_Geometry.active_state_value),
                  "active_state_value", level);
            }
            break;

        case SE_CLS_DRM_STROBING_LIGHT_BEHAVIOUR:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Strobing_Light_Behaviour.period: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Strobing_Light_Behaviour.period));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Strobing_Light_Behaviour.delay: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Strobing_Light_Behaviour.delay));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "period: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Strobing_Light_Behaviour.period));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "delay: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Strobing_Light_Behaviour.delay));
            }
            break;

        case SE_CLS_DRM_SYMBOL:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Symbol.name", name_ptr);
                SE_PrintString(&(field_ptr->u.Symbol.name), name_buffer,
                  level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Symbol.symbol_format: %s\n",name_ptr,
                        SE_PrintSymbolFormat
                    (field_ptr->u.Symbol.symbol_format));
                sprintf(name_buffer,"%s->u.Symbol.symbol_urn", name_ptr);
                SE_PrintURN(&(field_ptr->u.Symbol.symbol_urn), name_buffer,
                  level);
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Symbol.name), "name", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "symbol_format: %s\n",SE_PrintSymbolFormat
                    (field_ptr->u.Symbol.symbol_format));
                SE_PrintURN(&(field_ptr->u.Symbol.symbol_urn), "symbol_urn",
                  level);
            }
            break;

        case SE_CLS_DRM_TABLE_PROPERTY_DESCRIPTION:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Table_Property_Description.meaning", name_ptr);
                SE_PrintElementType
                (&(field_ptr->u.Table_Property_Description.meaning),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Table_Property_Description.value_unit:"\
                        " %s\n",name_ptr, EDCS_PrintUnitCode
                    (field_ptr->u.Table_Property_Description.value_unit));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Table_Property_Description.value_scale:"\
                        " %s\n",name_ptr, EDCS_PrintUnitScaleCode
                    (field_ptr->u.Table_Property_Description.value_scale));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Table_Property_Description.value_type:"\
                        " %s\n",name_ptr, SE_PrintDataTableDataValueType
                    (field_ptr->u.Table_Property_Description.value_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Table_Property_Description.component_data_table_ecc:"\
                        " %s\n",name_ptr, EDCS_PrintClassificationCode
                    (field_ptr->u.Table_Property_Description.component_data_table_ecc));
            }
            else
            {
                SE_PrintElementType
                (&(field_ptr->u.Table_Property_Description.meaning),
                  "meaning", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_unit: %s\n",EDCS_PrintUnitCode
                    (field_ptr->u.Table_Property_Description.value_unit));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_scale: %s\n",EDCS_PrintUnitScaleCode
                    (field_ptr->u.Table_Property_Description.value_scale));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_type: %s\n",
                        SE_PrintDataTableDataValueType
                    (field_ptr->u.Table_Property_Description.value_type));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "component_data_table_ecc: %s\n",
                        EDCS_PrintClassificationCode
                    (field_ptr->u.Table_Property_Description.component_data_table_ecc));
            }
            break;

        case SE_CLS_DRM_TEXT:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Text.text_string", name_ptr);
                SE_PrintString(&(field_ptr->u.Text.text_string), name_buffer,
                  level);
                sprintf(name_buffer,"%s->u.Text.font", name_ptr);
                SE_PrintTextFont(&(field_ptr->u.Text.font), name_buffer,
                  level);
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Text.text_string),
                  "text_string", level);
                SE_PrintTextFont(&(field_ptr->u.Text.font), "font", level);
            }
            break;

        case SE_CLS_DRM_TEXTURE_COORDINATE:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Texture_Coordinate.s: %s\n", name_ptr,
                        SE_PrintLongFloat(field_ptr->u.Texture_Coordinate.s));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Texture_Coordinate.t: %s\n", name_ptr,
                        SE_PrintLongFloat(field_ptr->u.Texture_Coordinate.t));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "s: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Texture_Coordinate.s));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "t: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Texture_Coordinate.t));
            }
            break;

        case SE_CLS_DRM_TEXTURE_COORDINATE_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Texture_Coordinate_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Texture_Coordinate_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Texture_Coordinate_Control_Link.s_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Texture_Coordinate_Control_Link.s_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Texture_Coordinate_Control_Link.t_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Texture_Coordinate_Control_Link.t_expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Texture_Coordinate_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "s_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Texture_Coordinate_Control_Link.s_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "t_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Texture_Coordinate_Control_Link.t_expression_index));
            }
            break;

        case SE_CLS_DRM_TIME_INTERVAL:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Time_Interval.time_significance: %s\n",
                        name_ptr, SE_PrintTimeSignificance
                    (field_ptr->u.Time_Interval.time_significance));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "time_significance: %s\n",
                        SE_PrintTimeSignificance
                    (field_ptr->u.Time_Interval.time_significance));
            }
            break;

        case SE_CLS_DRM_TIME_OF_DAY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Time_Of_Day.time_significance: %s\n",
                        name_ptr, SE_PrintTimeSignificance
                    (field_ptr->u.Time_Of_Day.time_significance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Time_Of_Day.time_of_day: %s\n",name_ptr,
                        SE_PrintTimeOfDay
                    (field_ptr->u.Time_Of_Day.time_of_day));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "time_significance: %s\n",
                        SE_PrintTimeSignificance
                    (field_ptr->u.Time_Of_Day.time_significance));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "time_of_day: %s\n",SE_PrintTimeOfDay
                    (field_ptr->u.Time_Of_Day.time_of_day));
            }
            break;

        case SE_CLS_DRM_TIME_POINT:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Time_Point.time_significance: %s\n",
                        name_ptr, SE_PrintTimeSignificance
                    (field_ptr->u.Time_Point.time_significance));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "time_significance: %s\n",
                        SE_PrintTimeSignificance
                    (field_ptr->u.Time_Point.time_significance));
            }
            break;

        case SE_CLS_DRM_TIME_RELATED_FEATURES:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Time_Related_Features.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Time_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Time_Related_Features.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Time_Related_Features.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Time_Related_Features.time_data_type:"\
                        " %s\n",name_ptr, SE_PrintTimeDataType
                    (field_ptr->u.Time_Related_Features.time_data_type));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Time_Related_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Time_Related_Features.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "time_data_type: %s\n",SE_PrintTimeDataType
                    (field_ptr->u.Time_Related_Features.time_data_type));
            }
            break;

        case SE_CLS_DRM_TIME_RELATED_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Time_Related_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Time_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Time_Related_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Time_Related_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Time_Related_Geometry.time_data_type:"\
                        " %s\n",name_ptr, SE_PrintTimeDataType
                    (field_ptr->u.Time_Related_Geometry.time_data_type));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Time_Related_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Time_Related_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "time_data_type: %s\n",SE_PrintTimeDataType
                    (field_ptr->u.Time_Related_Geometry.time_data_type));
            }
            break;

        case SE_CLS_DRM_TM_AUGMENTED_3D_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.TM_Augmented_3D_Location.coordinate",
                        name_ptr);
                SRM_PrintMapProjection3DCoordinate
                (&(field_ptr->u.TM_Augmented_3D_Location.coordinate),
                  name_buffer, level);
            }
            else
            {
                SRM_PrintMapProjection3DCoordinate
                (&(field_ptr->u.TM_Augmented_3D_Location.coordinate),
                  "coordinate", level);
            }
            break;

        case SE_CLS_DRM_TM_SURFACE_LOCATION:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.TM_Surface_Location.coordinate",
                        name_ptr);
                SRM_PrintMapProjectionSurfaceCoordinate
                (&(field_ptr->u.TM_Surface_Location.coordinate), name_buffer,
                  level);
            }
            else
            {
                SRM_PrintMapProjectionSurfaceCoordinate
                (&(field_ptr->u.TM_Surface_Location.coordinate), "coordinate",
                  level);
            }
            break;

        case SE_CLS_DRM_TRANSLATION:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Translation.axis: %s\n",name_ptr,
                        SE_PrintLSRTransformationAxis
                    (field_ptr->u.Translation.axis));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Translation.translation_amount: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Translation.translation_amount));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "axis: %s\n",SE_PrintLSRTransformationAxis
                    (field_ptr->u.Translation.axis));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "translation_amount: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Translation.translation_amount));
            }
            break;

        case SE_CLS_DRM_TRANSLATION_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Translation_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Translation_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Translation_Control_Link.expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Translation_Control_Link.expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Translation_Control_Link.lower_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Translation_Control_Link.lower_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Translation_Control_Link.upper_expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerUnsigned
                        (field_ptr->u.Translation_Control_Link.upper_expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Translation_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "expression_index: %s\n",
                        SE_PrintIntegerPositive
                        (field_ptr->u.Translation_Control_Link.expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "lower_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Translation_Control_Link.lower_expression_index));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "upper_expression_index: %s\n",
                        SE_PrintIntegerUnsigned
                        (field_ptr->u.Translation_Control_Link.upper_expression_index));
            }
            break;

        case SE_CLS_DRM_TRANSLUCENCY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Translucency.translucency_value: %s\n",
                        name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Translucency.translucency_value));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "translucency_value: %s\n", SE_PrintLongFloat
                        (field_ptr->u.Translucency.translucency_value));
            }
            break;

        case SE_CLS_DRM_TRANSLUCENCY_CONTROL_LINK:
            if (name_ptr)
            {
                sprintf(name_buffer,
                        "%s->u.Translucency_Control_Link.description",
                        name_ptr);
                SE_PrintString
                (&(field_ptr->u.Translucency_Control_Link.description),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Translucency_Control_Link.expression_index:"\
                        " %s\n", name_ptr, SE_PrintIntegerPositive
                        (field_ptr->u.Translucency_Control_Link.expression_index));
            }
            else
            {
                SE_PrintString
                (&(field_ptr->u.Translucency_Control_Link.description),
                  "description", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "expression_index: %s\n",
                        SE_PrintIntegerPositive
                        (field_ptr->u.Translucency_Control_Link.expression_index));
            }
            break;

        case SE_CLS_DRM_TRANSMITTAL_ROOT:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Transmittal_Root.name", name_ptr);
                SE_PrintString(&(field_ptr->u.Transmittal_Root.name),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Root.major_DRM_version:"\
                        " %s\n", name_ptr, SE_PrintShortIntegerPositive
                        (field_ptr->u.Transmittal_Root.major_DRM_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Root.minor_DRM_version:"\
                        " %s\n", name_ptr, SE_PrintByteUnsigned
                        (field_ptr->u.Transmittal_Root.minor_DRM_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Root.interim_DRM_version:"\
                        " %s\n", name_ptr, SE_PrintCharacter
                        (field_ptr->u.Transmittal_Root.interim_DRM_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Root.major_EDCS_version:"\
                        " %s\n", name_ptr, SE_PrintShortIntegerPositive
                        (field_ptr->u.Transmittal_Root.major_EDCS_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Root.minor_EDCS_version:"\
                        " %s\n", name_ptr, SE_PrintByteUnsigned
                        (field_ptr->u.Transmittal_Root.minor_EDCS_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Root.interim_EDCS_version:"\
                        " %s\n", name_ptr, SE_PrintCharacter
                        (field_ptr->u.Transmittal_Root.interim_EDCS_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Root.major_SRM_version:"\
                        " %s\n", name_ptr, SE_PrintShortIntegerPositive
                        (field_ptr->u.Transmittal_Root.major_SRM_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Root.minor_SRM_version:"\
                        " %s\n", name_ptr, SE_PrintByteUnsigned
                        (field_ptr->u.Transmittal_Root.minor_SRM_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Root.interim_SRM_version:"\
                        " %s\n", name_ptr, SE_PrintCharacter
                        (field_ptr->u.Transmittal_Root.interim_SRM_version));
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Transmittal_Root.name), "name",
                  level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "major_DRM_version: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Transmittal_Root.major_DRM_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "minor_DRM_version: %s\n", SE_PrintByteUnsigned
                        (field_ptr->u.Transmittal_Root.minor_DRM_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "interim_DRM_version: %s\n", SE_PrintCharacter
                        (field_ptr->u.Transmittal_Root.interim_DRM_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "major_EDCS_version: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Transmittal_Root.major_EDCS_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "minor_EDCS_version: %s\n", SE_PrintByteUnsigned
                        (field_ptr->u.Transmittal_Root.minor_EDCS_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "interim_EDCS_version: %s\n", SE_PrintCharacter
                        (field_ptr->u.Transmittal_Root.interim_EDCS_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "major_SRM_version: %s\n",
                        SE_PrintShortIntegerPositive
                        (field_ptr->u.Transmittal_Root.major_SRM_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "minor_SRM_version: %s\n", SE_PrintByteUnsigned
                        (field_ptr->u.Transmittal_Root.minor_SRM_version));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "interim_SRM_version: %s\n", SE_PrintCharacter
                        (field_ptr->u.Transmittal_Root.interim_SRM_version));
            }
            break;

        case SE_CLS_DRM_TRANSMITTAL_SUMMARY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Summary.features_present:"\
                        " %s\n",name_ptr, SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.features_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Summary.geometry_present:"\
                        " %s\n",name_ptr, SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.geometry_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Transmittal_Summary.geometry_topology_present:"\
                        " %s\n",name_ptr, SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.geometry_topology_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Transmittal_Summary.data_tables_present:"\
                        " %s\n",name_ptr, SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.data_tables_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Transmittal_Summary.priority_values_present:"\
                        " %s\n",name_ptr, SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.priority_values_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Transmittal_Summary.mobility_values_present:"\
                        " %s\n",name_ptr, SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.mobility_values_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Transmittal_Summary.thermal_values_present:"\
                        " %s\n",name_ptr, SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.thermal_values_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Transmittal_Summary.terrain_lods_present:"\
                        " %s\n",name_ptr, SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.terrain_lods_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Transmittal_Summary.two_D_features_flag:"\
                        " %s\n",name_ptr, SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.two_D_features_flag));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Summary.models_present:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Transmittal_Summary.models_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Summary.images_present:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Transmittal_Summary.images_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Summary.sounds_present:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Transmittal_Summary.sounds_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Summary.symbols_present:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Transmittal_Summary.symbols_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Summary.colours_present:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Transmittal_Summary.colours_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Transmittal_Summary.colour_model: %s\n",
                        name_ptr, SE_PrintColourModel
                    (field_ptr->u.Transmittal_Summary.colour_model));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Transmittal_Summary.EDCS_usage_list_is_complete:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Transmittal_Summary.EDCS_usage_list_is_complete));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "features_present: %s\n",SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.features_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "geometry_present: %s\n",SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.geometry_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "geometry_topology_present: %s\n",
                        SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.geometry_topology_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "data_tables_present: %s\n",SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.data_tables_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "priority_values_present: %s\n",
                        SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.priority_values_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "mobility_values_present: %s\n",
                        SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.mobility_values_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "thermal_values_present: %s\n",SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.thermal_values_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "terrain_lods_present: %s\n",SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.terrain_lods_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "two_D_features_flag: %s\n",SE_PrintPresentIn
                    (field_ptr->u.Transmittal_Summary.two_D_features_flag));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "models_present: %s\n",SE_PrintBoolean
                    (field_ptr->u.Transmittal_Summary.models_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "images_present: %s\n",SE_PrintBoolean
                    (field_ptr->u.Transmittal_Summary.images_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "sounds_present: %s\n",SE_PrintBoolean
                    (field_ptr->u.Transmittal_Summary.sounds_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "symbols_present: %s\n",SE_PrintBoolean
                    (field_ptr->u.Transmittal_Summary.symbols_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "colours_present: %s\n",SE_PrintBoolean
                    (field_ptr->u.Transmittal_Summary.colours_present));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "colour_model: %s\n",SE_PrintColourModel
                    (field_ptr->u.Transmittal_Summary.colour_model));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "EDCS_usage_list_is_complete: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Transmittal_Summary.EDCS_usage_list_is_complete));
            }
            break;

        case SE_CLS_DRM_UNION_OF_FEATURE_TOPOLOGY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Union_Of_Feature_Topology.feature_topology_level:"\
                        " %s\n",name_ptr, SE_PrintFeatureTopologyLevel
                    (field_ptr->u.Union_Of_Feature_Topology.feature_topology_level));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "feature_topology_level: %s\n",
                        SE_PrintFeatureTopologyLevel
                    (field_ptr->u.Union_Of_Feature_Topology.feature_topology_level));
            }
            break;

        case SE_CLS_DRM_UNION_OF_FEATURES:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Union_Of_Features.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Union_Of_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Union_Of_Features.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Union_Of_Features.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Union_Of_Features.union_reason: %s\n",
                        name_ptr, SE_PrintUnionReason
                    (field_ptr->u.Union_Of_Features.union_reason));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Union_Of_Features.ordering_reason: %s\n",
                        name_ptr, SE_PrintOrderingReason
                    (field_ptr->u.Union_Of_Features.ordering_reason));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Union_Of_Features.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Union_Of_Features.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "union_reason: %s\n",SE_PrintUnionReason
                    (field_ptr->u.Union_Of_Features.union_reason));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "ordering_reason: %s\n",SE_PrintOrderingReason
                    (field_ptr->u.Union_Of_Features.ordering_reason));
            }
            break;

        case SE_CLS_DRM_UNION_OF_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Union_Of_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Union_Of_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Union_Of_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Union_Of_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Union_Of_Geometry.union_reason: %s\n",
                        name_ptr, SE_PrintUnionReason
                    (field_ptr->u.Union_Of_Geometry.union_reason));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Union_Of_Geometry.ordering_reason: %s\n",
                        name_ptr, SE_PrintOrderingReason
                    (field_ptr->u.Union_Of_Geometry.ordering_reason));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Union_Of_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Union_Of_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "union_reason: %s\n",SE_PrintUnionReason
                    (field_ptr->u.Union_Of_Geometry.union_reason));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "ordering_reason: %s\n",SE_PrintOrderingReason
                    (field_ptr->u.Union_Of_Geometry.ordering_reason));
            }
            break;

        case SE_CLS_DRM_UNION_OF_GEOMETRY_HIERARCHY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Union_Of_Geometry_Hierarchy.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Union_Of_Geometry_Hierarchy.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Union_Of_Geometry_Hierarchy.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Union_Of_Geometry_Hierarchy.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Union_Of_Geometry_Hierarchy.union_reason:"\
                        " %s\n",name_ptr, SE_PrintUnionReason
                    (field_ptr->u.Union_Of_Geometry_Hierarchy.union_reason));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Union_Of_Geometry_Hierarchy.ordering_reason:"\
                        " %s\n",name_ptr, SE_PrintOrderingReason
                    (field_ptr->u.Union_Of_Geometry_Hierarchy.ordering_reason));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Union_Of_Geometry_Hierarchy.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Union_Of_Geometry_Hierarchy.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "union_reason: %s\n",SE_PrintUnionReason
                    (field_ptr->u.Union_Of_Geometry_Hierarchy.union_reason));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "ordering_reason: %s\n",SE_PrintOrderingReason
                    (field_ptr->u.Union_Of_Geometry_Hierarchy.ordering_reason));
            }
            break;

        case SE_CLS_DRM_UNION_OF_GEOMETRY_TOPOLOGY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Union_Of_Geometry_Topology.geometry_topology_level:"\
                        " %s\n",name_ptr, SE_PrintGeometryTopologyLevel
                    (field_ptr->u.Union_Of_Geometry_Topology.geometry_topology_level));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "geometry_topology_level: %s\n",
                        SE_PrintGeometryTopologyLevel
                    (field_ptr->u.Union_Of_Geometry_Topology.geometry_topology_level));
            }
            break;

        case SE_CLS_DRM_UNION_OF_PRIMITIVE_GEOMETRY:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Union_Of_Primitive_Geometry.unique_descendants:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Union_Of_Primitive_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Union_Of_Primitive_Geometry.strict_organizing_principle:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Union_Of_Primitive_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Union_Of_Primitive_Geometry.union_reason:"\
                        " %s\n",name_ptr, SE_PrintUnionReason
                    (field_ptr->u.Union_Of_Primitive_Geometry.union_reason));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Union_Of_Primitive_Geometry.ordering_reason:"\
                        " %s\n",name_ptr, SE_PrintOrderingReason
                    (field_ptr->u.Union_Of_Primitive_Geometry.ordering_reason));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "unique_descendants: %s\n",SE_PrintBoolean
                    (field_ptr->u.Union_Of_Primitive_Geometry.unique_descendants));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "strict_organizing_principle: %s\n",
                        SE_PrintBoolean
                    (field_ptr->u.Union_Of_Primitive_Geometry.strict_organizing_principle));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "union_reason: %s\n",SE_PrintUnionReason
                    (field_ptr->u.Union_Of_Primitive_Geometry.union_reason));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "ordering_reason: %s\n",SE_PrintOrderingReason
                    (field_ptr->u.Union_Of_Primitive_Geometry.ordering_reason));
            }
            break;

        case SE_CLS_DRM_VARIABLE:
            if (name_ptr)
            {
                sprintf(name_buffer,"%s->u.Variable.name", name_ptr);
                SE_PrintString(&(field_ptr->u.Variable.name), name_buffer,
                  level);
                sprintf(name_buffer,"%s->u.Variable.meaning", name_ptr);
                SE_PrintPropertyCode(&(field_ptr->u.Variable.meaning),
                  name_buffer, level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Variable.value_unit: %s\n",name_ptr,
                        EDCS_PrintUnitCode(field_ptr->u.Variable.value_unit));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Variable.value_scale: %s\n",name_ptr,
                        EDCS_PrintUnitScaleCode
                    (field_ptr->u.Variable.value_scale));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Variable.value_type: %s\n",name_ptr,
                        EDCS_PrintAttributeValueType
                    (field_ptr->u.Variable.value_type));
                sprintf(name_buffer,"%s->u.Variable.description", name_ptr);
                SE_PrintString(&(field_ptr->u.Variable.description),
                  name_buffer, level);
            }
            else
            {
                SE_PrintString(&(field_ptr->u.Variable.name), "name", level);
                SE_PrintPropertyCode(&(field_ptr->u.Variable.meaning),
                  "meaning", level);
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_unit: %s\n",EDCS_PrintUnitCode
                    (field_ptr->u.Variable.value_unit));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_scale: %s\n",EDCS_PrintUnitScaleCode
                    (field_ptr->u.Variable.value_scale));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value_type: %s\n",EDCS_PrintAttributeValueType
                    (field_ptr->u.Variable.value_type));
                SE_PrintString(&(field_ptr->u.Variable.description),
                  "description", level);
            }
            break;

        case SE_CLS_DRM_VOLUME_LIGHT_BEHAVIOUR:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Volume_Light_Behaviour.use_full_intensity:"\
                        " %s\n",name_ptr, SE_PrintBoolean
                    (field_ptr->u.Volume_Light_Behaviour.use_full_intensity));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, 
                        "%s->u.Volume_Light_Behaviour.minimum_colour_intensity:"\
                        " %s\n", name_ptr, SE_PrintLongFloat
                        (field_ptr->u.Volume_Light_Behaviour.minimum_colour_intensity));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "use_full_intensity: %s\n",SE_PrintBoolean
                    (field_ptr->u.Volume_Light_Behaviour.use_full_intensity));
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "minimum_colour_intensity: %s\n",
                        SE_PrintLongFloat
                        (field_ptr->u.Volume_Light_Behaviour.minimum_colour_intensity));
            }
            break;

        case SE_CLS_DRM_VOLUME_LOD_DATA:
            if (name_ptr)
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "%s->u.Volume_LOD_Data.outside: %s\n",name_ptr,
                        SE_PrintBoolean(field_ptr->u.Volume_LOD_Data.outside));
            }
            else
            {
                SE_LinkIndent(level, f_ptr);
                fprintf(f_ptr, "outside: %s\n",SE_PrintBoolean
                    (field_ptr->u.Volume_LOD_Data.outside));
            }
            break;

        case SE_CLS_DRM_WORLD_3X3:
            if (name_ptr)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->u.World_3x3.world_3x3: %s\n", name_ptr,
                        SRM_PrintMatrix3x3(field_ptr->u.World_3x3.world_3x3));
            }
            else
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "world_3x3: %s\n", SRM_PrintMatrix3x3
                        (field_ptr->u.World_3x3.world_3x3));
            }
            break;


        default:
             /* Classes that do not have fields */
             break;
    }
    SRM_SetOutFilePtr(orig_srm_f_ptr);
    EDCS_SetOutFilePtr(orig_edcs_f_ptr);
} /* end SE_PrintDRMClassFields */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintAddress
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintAddress
(
    const SE_Address *value_ptr,
    const char       *name_ptr,
          SE_Integer_Unsigned  level
)
{
    char  buffer[1024];
    FILE *f_ptr;
    SE_Integer_Unsigned i;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Address\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->delivery_point_count: %s\n", name_ptr,
                SE_PrintShortIntegerPositive(value_ptr->delivery_point_count));
        if ((value_ptr->delivery_point_count > 0) &&
            (value_ptr->delivery_point != NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned)
                value_ptr->delivery_point_count; i++)
            {
                sprintf(buffer, "%s->delivery_point[%u]", name_ptr, i);
                SE_PrintString(&(value_ptr->delivery_point[i]), buffer, level);
            } /* end for i */
        }
        sprintf(buffer, "%s->city", name_ptr);
        SE_PrintString(&(value_ptr->city), buffer, level);
        sprintf(buffer, "%s->administrative_area", name_ptr);
        SE_PrintString(&(value_ptr->administrative_area), buffer, level);
        sprintf(buffer, "%s->postal_code", name_ptr);
        SE_PrintString(&(value_ptr->postal_code), buffer, level);
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->country[0..2]: ", name_ptr);
        for (i = 0; i < 3; i++)
        {
            fprintf(f_ptr, "%c", value_ptr->country[i]);
        } /* end for i */
        fprintf(f_ptr, "\n");
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->email_address_count: %s\n", name_ptr,
                SE_PrintShortIntegerPositive(value_ptr->email_address_count));
        if ((value_ptr->email_address_count > 0) && (value_ptr->email_address
            != NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned)
                value_ptr->email_address_count; i++)
            {
                sprintf(buffer, "%s->email_address[%u]", name_ptr, i);
                SE_PrintString(&(value_ptr->email_address[i]), buffer, level);
            } /* end for i */
        }
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "delivery_point_count: %s\n",
                SE_PrintShortIntegerPositive(value_ptr->delivery_point_count));
        if ((value_ptr->delivery_point_count > 0) &&
            (value_ptr->delivery_point != NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned)
                value_ptr->delivery_point_count; i++)
            {
                sprintf(buffer, "delivery_point[%u]", i);
                SE_PrintString(&(value_ptr->delivery_point[i]), buffer, level);
            } /* end for i */
        }
        sprintf(buffer, "city");
        SE_PrintString(&(value_ptr->city), buffer, level);
        sprintf(buffer, "administrative_area");
        SE_PrintString(&(value_ptr->administrative_area), buffer, level);
        sprintf(buffer, "postal_code");
        SE_PrintString(&(value_ptr->postal_code), buffer, level);
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "country[0..2]: ");
        for (i = 0; i < 3; i++)
        {
            fprintf(f_ptr, "%c", value_ptr->country[i]);
        } /* end for i */
        fprintf(f_ptr, "\n");
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "email_address_count: %s\n",
                SE_PrintShortIntegerPositive(value_ptr->email_address_count));
        if ((value_ptr->email_address_count > 0) && (value_ptr->email_address
            != NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned)
                value_ptr->email_address_count; i++)
            {
                sprintf(buffer, "email_address[%u]", i);
                SE_PrintString(&(value_ptr->email_address[i]), buffer, level);
            } /* end for i */
        }
    }
} /* end SE_PrintAddress */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintAPI
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintAPI
(
    SE_API value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_API_SRM:
             return "SE_API_SRM";

        case SE_API_EDCS:
             return "SE_API_EDCS";

        case SE_API_DRM:
             return "SE_API_DRM";

        case SE_API_TACCESS0:
             return "SE_API_TACCESS0";

        case SE_API_TACCESS1:
             return "SE_API_TACCESS1";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_API VALUE (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintAPI */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintAxisAlignment
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintAxisAlignment
(
    SE_Axis_Alignment value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_AXALGN_NONE:
             return "SE_AXALGN_NONE";

        case SE_AXALGN_LOWER:
             return "SE_AXALGN_LOWER";

        case SE_AXALGN_MEDIAN:
             return "SE_AXALGN_MEDIAN";

        case SE_AXALGN_UPPER:
             return "SE_AXALGN_UPPER";

        case SE_AXALGN_GEOMETRIC_MEAN:
             return "SE_AXALGN_GEOMETRIC_MEAN";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Axis_Alignment VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintAxisAlignment */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintBoolean
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintBoolean
(
    SE_Boolean value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_FALSE:
             return "SE_FALSE";

        case SE_TRUE:
             return "SE_TRUE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Boolean VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintBoolean */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintByte
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintByte
(
    SE_Byte value
)
{
    static char buffer[100];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%i", (int) value);
    return buffer;
} /* end SE_PrintByte */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintBytePositive
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintBytePositive
(
    SE_Byte_Positive value
)
{
    static char buffer[100];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%u", (unsigned int) value);
    return buffer;
} /* end SE_PrintBytePositive */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintByteUnsigned
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintByteUnsigned
(
    SE_Byte_Unsigned value
)
{
    static char buffer[100];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%u", (unsigned int) value);
    return buffer;
} /* end SE_PrintByteUnsigned */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintCameraProjectionType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintCameraProjectionType
(
    SE_Camera_Projection_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_CAM_ORTHOGRAPHIC:
             return "SE_CAM_ORTHOGRAPHIC";

        case SE_CAM_PERSPECTIVE:
             return "SE_CAM_PERSPECTIVE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Camera_Projection_Type VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintCameraProjectionType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintCharacter
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintCharacter
(
    SE_Character value
)
{
    static char buffer[10];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%c", value);
    return buffer;
} /* end SE_PrintCharacter */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintCIOnlineFunctionCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintCIOnlineFunctionCode
(
    SE_CI_OnlineFunctionCode value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_CIOLFCOD_DOWNLOAD:
             return "SE_CIOLFCOD_DOWNLOAD";

        case SE_CIOLFCOD_INFORMATION:
             return "SE_CIOLFCOD_INFORMATION";

        case SE_CIOLFCOD_OFFLINE_ACCESS:
             return "SE_CIOLFCOD_OFFLINE_ACCESS";

        case SE_CIOLFCOD_ORDER:
             return "SE_CIOLFCOD_ORDER";

        case SE_CIOLFCOD_SEARCH:
             return "SE_CIOLFCOD_SEARCH";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_CI_OnlineFunctionCode VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintCIOnlineFunctionCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintCIOnlineResource
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintCIOnlineResource
(
    const SE_CI_OnlineResource *value_ptr,
    const char                 *name_ptr,
          SE_Integer_Unsigned   level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_CI_OnlineResource\n");
        return;
    }
    if (name_ptr)
    {
        sprintf(buffer, "%s->linkage", name_ptr);
        SE_PrintURL(&(value_ptr->linkage), buffer, level);
        sprintf(buffer, "%s->protocol", name_ptr);
        SE_PrintString(&(value_ptr->protocol), buffer, level);
        sprintf(buffer, "%s->application_profile", name_ptr);
        SE_PrintString(&(value_ptr->application_profile), buffer, level);
        sprintf(buffer, "%s->name", name_ptr);
        SE_PrintString(&(value_ptr->name), buffer, level);
        sprintf(buffer, "%s->description", name_ptr);
        SE_PrintString(&(value_ptr->description), buffer, level);
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->function: %s\n", name_ptr,
                SE_PrintCIOnlineFunctionCode(value_ptr->function));
    }
    else
    {
        sprintf(buffer, "linkage");
        SE_PrintURL(&(value_ptr->linkage), buffer, level);
        sprintf(buffer, "protocol");
        SE_PrintString(&(value_ptr->protocol), buffer, level);
        sprintf(buffer, "application_profile");
        SE_PrintString(&(value_ptr->application_profile), buffer, level);
        sprintf(buffer, "name");
        SE_PrintString(&(value_ptr->name), buffer, level);
        sprintf(buffer, "description");
        SE_PrintString(&(value_ptr->description), buffer, level);
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "function: %s\n",
                SE_PrintCIOnlineFunctionCode(value_ptr->function));
    }
} /* end SE_PrintCIOnlineResource */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintCIRoleCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintCIRoleCode
(
    SE_CI_RoleCode value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_ROLECOD_RESOURCE_PROVIDER:
             return "SE_ROLECOD_RESOURCE_PROVIDER";

        case SE_ROLECOD_CUSTODIAN:
             return "SE_ROLECOD_CUSTODIAN";

        case SE_ROLECOD_OWNER:
             return "SE_ROLECOD_OWNER";

        case SE_ROLECOD_USER:
             return "SE_ROLECOD_USER";

        case SE_ROLECOD_DISTRIBUTOR:
             return "SE_ROLECOD_DISTRIBUTOR";

        case SE_ROLECOD_ORIGINATOR:
             return "SE_ROLECOD_ORIGINATOR";

        case SE_ROLECOD_POINT_OF_CONTACT:
             return "SE_ROLECOD_POINT_OF_CONTACT";

        case SE_ROLECOD_PRINCIPAL_INVESTIGATOR:
             return "SE_ROLECOD_PRINCIPAL_INVESTIGATOR";

        case SE_ROLECOD_PROCESSOR:
             return "SE_ROLECOD_PROCESSOR";

        case SE_ROLECOD_PUBLISHER:
             return "SE_ROLECOD_PUBLISHER";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_CI_RoleCode VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintCIRoleCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintCMYData
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintCMYData
(
    const SE_CMY_Data *value_ptr,
    const char        *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_CMY_Data\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->cyan: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->cyan));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->magenta: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->magenta));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->yellow: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->yellow));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "cyan: %s\n", SE_PrintLongFloat(value_ptr->cyan));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "magenta: %s\n", SE_PrintLongFloat(value_ptr->magenta));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "yellow: %s\n", SE_PrintLongFloat(value_ptr->yellow));
    }
} /* end SE_PrintCMYData */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintCMYKData
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintCMYKData
(
    const SE_CMYK_Data *value_ptr,
    const char         *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_CMYK_Data\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->cyan: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->cyan));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->magenta: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->magenta));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->yellow: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->yellow));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->black: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->black));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "cyan: %s\n", SE_PrintLongFloat(value_ptr->cyan));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "magenta: %s\n", SE_PrintLongFloat(value_ptr->magenta));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "yellow: %s\n", SE_PrintLongFloat(value_ptr->yellow));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "black: %s\n", SE_PrintLongFloat(value_ptr->black));
    }
} /* end SE_PrintCMYKData */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintColourBinding
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintColourBinding
(
    SE_Colour_Binding value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_COLRB_NORMAL:
             return "SE_COLRB_NORMAL";

        case SE_COLRB_PARENT_OVERRIDE:
             return "SE_COLRB_PARENT_OVERRIDE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Colour_Binding VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintColourBinding */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintColourData
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintColourData
(
    const SE_Colour_Data *value_ptr,
    const char           *name_ptr,
          SE_Integer_Unsigned  level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Colour_Data\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->colour_model: %s\n", name_ptr,
                SE_PrintColourModel(value_ptr->colour_model));
        switch (value_ptr->colour_model)
        {
            case SE_COLRMOD_RGB:
                sprintf(buffer, "%s->u.rgb", name_ptr);
                SE_PrintRGBData(&(value_ptr->u.rgb), buffer, level);
                break;

            case SE_COLRMOD_CMY:
                sprintf(buffer, "%s->u.cmy", name_ptr);
                SE_PrintCMYData(&(value_ptr->u.cmy), buffer, level);
                break;

            case SE_COLRMOD_HSV:
                sprintf(buffer, "%s->u.hsv", name_ptr);
                SE_PrintHSVData(&(value_ptr->u.hsv), buffer, level);
                break;

        } /* end switch */
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "colour_model: %s\n",
                SE_PrintColourModel(value_ptr->colour_model));
        switch (value_ptr->colour_model)
        {
            case SE_COLRMOD_RGB:
                sprintf(buffer, "u.rgb");
                SE_PrintRGBData(&(value_ptr->u.rgb), buffer, level);
                break;

            case SE_COLRMOD_CMY:
                sprintf(buffer, "u.cmy");
                SE_PrintCMYData(&(value_ptr->u.cmy), buffer, level);
                break;

            case SE_COLRMOD_HSV:
                sprintf(buffer, "u.hsv");
                SE_PrintHSVData(&(value_ptr->u.hsv), buffer, level);
                break;

        } /* end switch */
    }
} /* end SE_PrintColourData */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintColourMapping
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintColourMapping
(
    const SE_Colour_Mapping *value_ptr,
    const char              *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Colour_Mapping\n");
        return;
    }
    if (name_ptr)
    {
    if (value_ptr->member.Front_Primary)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Front_Primary\n", name_ptr);
    }
    if (value_ptr->member.Front_Distance_Blend)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Front_Distance_Blend\n", name_ptr);
    }
    if (value_ptr->member.Front_Image_Blend)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Front_Image_Blend\n", name_ptr);
    }
    if (value_ptr->member.Back_Primary)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Back_Primary\n", name_ptr);
    }
    if (value_ptr->member.Back_Distance_Blend)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Back_Distance_Blend\n", name_ptr);
    }
    if (value_ptr->member.Back_Image_Blend)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Back_Image_Blend\n", name_ptr);
    }
    if (value_ptr->member.Primary_Light_Rendering_Behaviour)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Primary_Light_Rendering_Behaviour\n",
        name_ptr);
    }
    if (value_ptr->member.Secondary_Light_Rendering_Behaviour)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Secondary_Light_Rendering_Behaviour\n",
        name_ptr);
    }
    }
    else
    {
    if (value_ptr->member.Front_Primary)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Front_Primary\n");
    }
    if (value_ptr->member.Front_Distance_Blend)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Front_Distance_Blend\n");
    }
    if (value_ptr->member.Front_Image_Blend)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Front_Image_Blend\n");
    }
    if (value_ptr->member.Back_Primary)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Back_Primary\n");
    }
    if (value_ptr->member.Back_Distance_Blend)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Back_Distance_Blend\n");
    }
    if (value_ptr->member.Back_Image_Blend)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Back_Image_Blend\n");
    }
    if (value_ptr->member.Primary_Light_Rendering_Behaviour)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Primary_Light_Rendering_Behaviour\n");
    }
    if (value_ptr->member.Secondary_Light_Rendering_Behaviour)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Secondary_Light_Rendering_Behaviour\n");
    }
    }
} /* end SE_PrintColourMapping */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintColourModel
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintColourModel
(
    SE_Colour_Model value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_COLRMOD_RGB:
             return "SE_COLRMOD_RGB";

        case SE_COLRMOD_CMY:
             return "SE_COLRMOD_CMY";

        case SE_COLRMOD_HSV:
             return "SE_COLRMOD_HSV";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Colour_Model VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintColourModel */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintContactInformation
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintContactInformation
(
    const SE_Contact_Information *value_ptr,
    const char                   *name_ptr,
          SE_Integer_Unsigned     level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Contact_Information\n");
        return;
    }
    if (name_ptr)
    {
        sprintf(buffer, "%s->phone", name_ptr);
        SE_PrintTelephoneInformation(&(value_ptr->phone), buffer, level);
        sprintf(buffer, "%s->address", name_ptr);
        SE_PrintAddress(&(value_ptr->address), buffer, level);
        sprintf(buffer, "%s->online_resource", name_ptr);
        SE_PrintCIOnlineResource(&(value_ptr->online_resource), buffer, level);
        sprintf(buffer, "%s->hours_of_service", name_ptr);
        SE_PrintString(&(value_ptr->hours_of_service), buffer, level);
        sprintf(buffer, "%s->contact_instructions", name_ptr);
        SE_PrintString(&(value_ptr->contact_instructions), buffer, level);
    }
    else
    {
        sprintf(buffer, "phone");
        SE_PrintTelephoneInformation(&(value_ptr->phone), buffer, level);
        sprintf(buffer, "address");
        SE_PrintAddress(&(value_ptr->address), buffer, level);
        sprintf(buffer, "online_resource");
        SE_PrintCIOnlineResource(&(value_ptr->online_resource), buffer, level);
        sprintf(buffer, "hours_of_service");
        SE_PrintString(&(value_ptr->hours_of_service), buffer, level);
        sprintf(buffer, "contact_instructions");
        SE_PrintString(&(value_ptr->contact_instructions), buffer, level);
    }
} /* end SE_PrintContactInformation */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintCountIntervalValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintCountIntervalValue
(
    const SE_Count_Interval_Value *value_ptr,
    const char                    *name_ptr,
          SE_Integer_Unsigned      level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Count_Interval_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->interval_type: %s\n", name_ptr,
                SE_PrintIntervalType(value_ptr->interval_type));
        switch (value_ptr->interval_type)
        {
            case SE_INTRVLTYP_OPEN_INTERVAL:
                sprintf(buffer, "%s->value.open_interval", name_ptr);
                EDCS_PrintCountInterval(&(value_ptr->value.open_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GE_LT_INTERVAL:
                sprintf(buffer, "%s->value.ge_lt_interval", name_ptr);
                EDCS_PrintCountInterval(&(value_ptr->value.ge_lt_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GT_LE_INTERVAL:
                sprintf(buffer, "%s->value.gt_le_interval", name_ptr);
                EDCS_PrintCountInterval(&(value_ptr->value.gt_le_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_CLOSED_INTERVAL:
                sprintf(buffer, "%s->value.closed_interval", name_ptr);
                EDCS_PrintCountInterval(&(value_ptr->value.closed_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.gt_semi_interval: %s\n", name_ptr,
                        EDCS_PrintCount(value_ptr->value.gt_semi_interval));
                break;

            case SE_INTRVLTYP_GE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.ge_semi_interval: %s\n", name_ptr,
                        EDCS_PrintCount(value_ptr->value.ge_semi_interval));
                break;

            case SE_INTRVLTYP_LT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.lt_semi_interval: %s\n", name_ptr,
                        EDCS_PrintCount(value_ptr->value.lt_semi_interval));
                break;

            case SE_INTRVLTYP_LE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.le_semi_interval: %s\n", name_ptr,
                        EDCS_PrintCount(value_ptr->value.le_semi_interval));
                break;

        } /* end switch */
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "interval_type: %s\n",
                SE_PrintIntervalType(value_ptr->interval_type));
        switch (value_ptr->interval_type)
        {
            case SE_INTRVLTYP_OPEN_INTERVAL:
                sprintf(buffer, "value.open_interval");
                EDCS_PrintCountInterval(&(value_ptr->value.open_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GE_LT_INTERVAL:
                sprintf(buffer, "value.ge_lt_interval");
                EDCS_PrintCountInterval(&(value_ptr->value.ge_lt_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GT_LE_INTERVAL:
                sprintf(buffer, "value.gt_le_interval");
                EDCS_PrintCountInterval(&(value_ptr->value.gt_le_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_CLOSED_INTERVAL:
                sprintf(buffer, "value.closed_interval");
                EDCS_PrintCountInterval(&(value_ptr->value.closed_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.gt_semi_interval: %s\n", EDCS_PrintCount
                        (value_ptr->value.gt_semi_interval));
                break;

            case SE_INTRVLTYP_GE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.ge_semi_interval: %s\n", EDCS_PrintCount
                        (value_ptr->value.ge_semi_interval));
                break;

            case SE_INTRVLTYP_LT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.lt_semi_interval: %s\n", EDCS_PrintCount
                        (value_ptr->value.lt_semi_interval));
                break;

            case SE_INTRVLTYP_LE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.le_semi_interval: %s\n", EDCS_PrintCount
                        (value_ptr->value.le_semi_interval));
                break;

        } /* end switch */
    }
} /* end SE_PrintCountIntervalValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintDataQualityElement
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintDataQualityElement
(
    const SE_Data_Quality_Element *value_ptr,
    const char                    *name_ptr,
          SE_Integer_Unsigned      level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Data_Quality_Element\n");
        return;
    }
    if (name_ptr)
    {
        sprintf(buffer, "%s->name_of_measure", name_ptr);
        SE_PrintString(&(value_ptr->name_of_measure), buffer, level);
        sprintf(buffer, "%s->measure_identification", name_ptr);
        SE_PrintString(&(value_ptr->measure_identification), buffer, level);
        sprintf(buffer, "%s->measure_description", name_ptr);
        SE_PrintString(&(value_ptr->measure_description), buffer, level);
        sprintf(buffer, "%s->evaluation_method_type", name_ptr);
        SE_PrintString(&(value_ptr->evaluation_method_type), buffer, level);
        sprintf(buffer, "%s->evaluation_method_description", name_ptr);
        SE_PrintString(&(value_ptr->evaluation_method_description), buffer,
          level);
        sprintf(buffer, "%s->evaluation_procedure", name_ptr);
        SE_PrintString(&(value_ptr->evaluation_procedure), buffer, level);
        sprintf(buffer, "%s->data_time", name_ptr);
        SE_PrintString(&(value_ptr->data_time), buffer, level);
        sprintf(buffer, "%s->result", name_ptr);
        SE_PrintString(&(value_ptr->result), buffer, level);
    }
    else
    {
        sprintf(buffer, "name_of_measure");
        SE_PrintString(&(value_ptr->name_of_measure), buffer, level);
        sprintf(buffer, "measure_identification");
        SE_PrintString(&(value_ptr->measure_identification), buffer, level);
        sprintf(buffer, "measure_description");
        SE_PrintString(&(value_ptr->measure_description), buffer, level);
        sprintf(buffer, "evaluation_method_type");
        SE_PrintString(&(value_ptr->evaluation_method_type), buffer, level);
        sprintf(buffer, "evaluation_method_description");
        SE_PrintString(&(value_ptr->evaluation_method_description), buffer,
          level);
        sprintf(buffer, "evaluation_procedure");
        SE_PrintString(&(value_ptr->evaluation_procedure), buffer, level);
        sprintf(buffer, "data_time");
        SE_PrintString(&(value_ptr->data_time), buffer, level);
        sprintf(buffer, "result");
        SE_PrintString(&(value_ptr->result), buffer, level);
    }
} /* end SE_PrintDataQualityElement */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintDataTableDataValueType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintDataTableDataValueType
(
    SE_Data_Table_Data_Value_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_DTDATAVALTYP_SINGLE_LONG_FLOAT:
             return "SE_DTDATAVALTYP_SINGLE_LONG_FLOAT";

        case SE_DTDATAVALTYP_LONG_FLOAT:
             return "SE_DTDATAVALTYP_LONG_FLOAT";

        case SE_DTDATAVALTYP_SINGLE_INTEGER:
             return "SE_DTDATAVALTYP_SINGLE_INTEGER";

        case SE_DTDATAVALTYP_INTEGER:
             return "SE_DTDATAVALTYP_INTEGER";

        case SE_DTDATAVALTYP_SINGLE_COUNT:
             return "SE_DTDATAVALTYP_SINGLE_COUNT";

        case SE_DTDATAVALTYP_COUNT:
             return "SE_DTDATAVALTYP_COUNT";

        case SE_DTDATAVALTYP_INDEX:
             return "SE_DTDATAVALTYP_INDEX";

        case SE_DTDATAVALTYP_STRING:
             return "SE_DTDATAVALTYP_STRING";

        case SE_DTDATAVALTYP_CONSTRAINED_STRING:
             return "SE_DTDATAVALTYP_CONSTRAINED_STRING";

        case SE_DTDATAVALTYP_KEY:
             return "SE_DTDATAVALTYP_KEY";

        case SE_DTDATAVALTYP_ENUMERATION:
             return "SE_DTDATAVALTYP_ENUMERATION";

        case SE_DTDATAVALTYP_BOOLEAN:
             return "SE_DTDATAVALTYP_BOOLEAN";

        case SE_DTDATAVALTYP_INDEX_CODE:
             return "SE_DTDATAVALTYP_INDEX_CODE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Data_Table_Data_Value_Type"\
                    " VALUE (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintDataTableDataValueType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintDisplaySide
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintDisplaySide
(
    const SE_Display_Side *value_ptr,
    const char            *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Display_Side\n");
        return;
    }
    if (name_ptr)
    {
    if (value_ptr->member.Front)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Front\n", name_ptr);
    }
    if (value_ptr->member.Back)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Back\n", name_ptr);
    }
    }
    else
    {
    if (value_ptr->member.Front)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Front\n");
    }
    if (value_ptr->member.Back)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Back\n");
    }
    }
} /* end SE_PrintDisplaySide */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintDisplayStyle
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintDisplayStyle
(
    const SE_Display_Style *value_ptr,
    const char             *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Display_Style\n");
        return;
    }
    if (name_ptr)
    {
    if (value_ptr->member.Solid)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Solid\n", name_ptr);
    }
    if (value_ptr->member.Wireframe)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Wireframe\n", name_ptr);
    }
    }
    else
    {
    if (value_ptr->member.Solid)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Solid\n");
    }
    if (value_ptr->member.Wireframe)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Wireframe\n");
    }
    }
} /* end SE_PrintDisplayStyle */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintDRMClass
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintDRMClass
(
    SE_DRM_Class value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_CLS_DRM_NULL:
             return "SE_CLS_DRM_NULL";

        case SE_CLS_DRM_ABSOLUTE_TIME:
             return "SE_CLS_DRM_ABSOLUTE_TIME";

        case SE_CLS_DRM_ABSOLUTE_TIME_INTERVAL:
             return "SE_CLS_DRM_ABSOLUTE_TIME_INTERVAL";

        case SE_CLS_DRM_AGGREGATE_FEATURE:
             return "SE_CLS_DRM_AGGREGATE_FEATURE";

        case SE_CLS_DRM_AGGREGATE_GEOMETRY:
             return "SE_CLS_DRM_AGGREGATE_GEOMETRY";

        case SE_CLS_DRM_ALTERNATE_HIERARCHY_RELATED_FEATURES:
             return "SE_CLS_DRM_ALTERNATE_HIERARCHY_RELATED_FEATURES";

        case SE_CLS_DRM_ALTERNATE_HIERARCHY_RELATED_GEOMETRY:
             return "SE_CLS_DRM_ALTERNATE_HIERARCHY_RELATED_GEOMETRY";

        case SE_CLS_DRM_AMBIENT_COLOUR:
             return "SE_CLS_DRM_AMBIENT_COLOUR";

        case SE_CLS_DRM_ANIMATION_BEHAVIOUR:
             return "SE_CLS_DRM_ANIMATION_BEHAVIOUR";

        case SE_CLS_DRM_ANIMATION_RELATED_GEOMETRY:
             return "SE_CLS_DRM_ANIMATION_RELATED_GEOMETRY";

        case SE_CLS_DRM_ARC:
             return "SE_CLS_DRM_ARC";

        case SE_CLS_DRM_AREAL_FEATURE:
             return "SE_CLS_DRM_AREAL_FEATURE";

        case SE_CLS_DRM_ATTACHMENT_POINT:
             return "SE_CLS_DRM_ATTACHMENT_POINT";

        case SE_CLS_DRM_AXIS:
             return "SE_CLS_DRM_AXIS";

        case SE_CLS_DRM_BASE_ASSOCIATION_DATA:
             return "SE_CLS_DRM_BASE_ASSOCIATION_DATA";

        case SE_CLS_DRM_BASE_LOD_DATA:
             return "SE_CLS_DRM_BASE_LOD_DATA";

        case SE_CLS_DRM_BASE_POSITIONAL_LIGHT:
             return "SE_CLS_DRM_BASE_POSITIONAL_LIGHT";

        case SE_CLS_DRM_BASE_SPATIAL_ASSOCIATION_DATA:
             return "SE_CLS_DRM_BASE_SPATIAL_ASSOCIATION_DATA";

        case SE_CLS_DRM_BASE_SUMMARY_ITEM:
             return "SE_CLS_DRM_BASE_SUMMARY_ITEM";

        case SE_CLS_DRM_BASE_TIME_DATA:
             return "SE_CLS_DRM_BASE_TIME_DATA";

        case SE_CLS_DRM_BLEND_DIRECTIONAL_LIGHT:
             return "SE_CLS_DRM_BLEND_DIRECTIONAL_LIGHT";

        case SE_CLS_DRM_BOUNDING_VOLUME:
             return "SE_CLS_DRM_BOUNDING_VOLUME";

        case SE_CLS_DRM_BROWSE_MEDIA:
             return "SE_CLS_DRM_BROWSE_MEDIA";

        case SE_CLS_DRM_CAMERA_POINT:
             return "SE_CLS_DRM_CAMERA_POINT";

        case SE_CLS_DRM_CC_3D_LOCATION:
             return "SE_CLS_DRM_CC_3D_LOCATION";

        case SE_CLS_DRM_CD_3D_LOCATION:
             return "SE_CLS_DRM_CD_3D_LOCATION";

        case SE_CLS_DRM_CD_SURFACE_LOCATION:
             return "SE_CLS_DRM_CD_SURFACE_LOCATION";

        case SE_CLS_DRM_CITATION:
             return "SE_CLS_DRM_CITATION";

        case SE_CLS_DRM_CLASSIFICATION_DATA:
             return "SE_CLS_DRM_CLASSIFICATION_DATA";

        case SE_CLS_DRM_CLASSIFICATION_RELATED_FEATURES:
             return "SE_CLS_DRM_CLASSIFICATION_RELATED_FEATURES";

        case SE_CLS_DRM_CLASSIFICATION_RELATED_GEOMETRY:
             return "SE_CLS_DRM_CLASSIFICATION_RELATED_GEOMETRY";

        case SE_CLS_DRM_CM_3D_LOCATION:
             return "SE_CLS_DRM_CM_3D_LOCATION";

        case SE_CLS_DRM_CMY_COLOUR:
             return "SE_CLS_DRM_CMY_COLOUR";

        case SE_CLS_DRM_CMY_COLOUR_CONTROL_LINK:
             return "SE_CLS_DRM_CMY_COLOUR_CONTROL_LINK";

        case SE_CLS_DRM_COLLISION_VOLUME:
             return "SE_CLS_DRM_COLLISION_VOLUME";

        case SE_CLS_DRM_COLOUR:
             return "SE_CLS_DRM_COLOUR";

        case SE_CLS_DRM_COLOUR_DATA:
             return "SE_CLS_DRM_COLOUR_DATA";

        case SE_CLS_DRM_COLOUR_INDEX:
             return "SE_CLS_DRM_COLOUR_INDEX";

        case SE_CLS_DRM_COLOUR_INDEX_CONTROL_LINK:
             return "SE_CLS_DRM_COLOUR_INDEX_CONTROL_LINK";

        case SE_CLS_DRM_COLOUR_SHININESS:
             return "SE_CLS_DRM_COLOUR_SHININESS";

        case SE_CLS_DRM_COLOUR_TABLE:
             return "SE_CLS_DRM_COLOUR_TABLE";

        case SE_CLS_DRM_COLOUR_TABLE_GROUP:
             return "SE_CLS_DRM_COLOUR_TABLE_GROUP";

        case SE_CLS_DRM_COLOUR_TABLE_LIBRARY:
             return "SE_CLS_DRM_COLOUR_TABLE_LIBRARY";

        case SE_CLS_DRM_CONE_DIRECTIONAL_LIGHT:
             return "SE_CLS_DRM_CONE_DIRECTIONAL_LIGHT";

        case SE_CLS_DRM_CONFORMAL_BEHAVIOUR:
             return "SE_CLS_DRM_CONFORMAL_BEHAVIOUR";

        case SE_CLS_DRM_CONTACT_POINT:
             return "SE_CLS_DRM_CONTACT_POINT";

        case SE_CLS_DRM_CONTINUOUS_LOD_RELATED_GEOMETRY:
             return "SE_CLS_DRM_CONTINUOUS_LOD_RELATED_GEOMETRY";

        case SE_CLS_DRM_CONTROL_LINK:
             return "SE_CLS_DRM_CONTROL_LINK";

        case SE_CLS_DRM_CYLINDRICAL_VOLUME_EXTENT:
             return "SE_CLS_DRM_CYLINDRICAL_VOLUME_EXTENT";

        case SE_CLS_DRM_DATA_QUALITY:
             return "SE_CLS_DRM_DATA_QUALITY";

        case SE_CLS_DRM_DATA_TABLE:
             return "SE_CLS_DRM_DATA_TABLE";

        case SE_CLS_DRM_DATA_TABLE_LIBRARY:
             return "SE_CLS_DRM_DATA_TABLE_LIBRARY";

        case SE_CLS_DRM_DIFFUSE_COLOUR:
             return "SE_CLS_DRM_DIFFUSE_COLOUR";

        case SE_CLS_DRM_DIRECTIONAL_LIGHT_BEHAVIOUR:
             return "SE_CLS_DRM_DIRECTIONAL_LIGHT_BEHAVIOUR";

        case SE_CLS_DRM_DISTANCE_LOD_DATA:
             return "SE_CLS_DRM_DISTANCE_LOD_DATA";

        case SE_CLS_DRM_DRM_CLASS_SUMMARY_ITEM:
             return "SE_CLS_DRM_DRM_CLASS_SUMMARY_ITEM";

        case SE_CLS_DRM_EC_AUGMENTED_3D_LOCATION:
             return "SE_CLS_DRM_EC_AUGMENTED_3D_LOCATION";

        case SE_CLS_DRM_EC_SURFACE_LOCATION:
             return "SE_CLS_DRM_EC_SURFACE_LOCATION";

        case SE_CLS_DRM_EDCS_USE_SUMMARY_ITEM:
             return "SE_CLS_DRM_EDCS_USE_SUMMARY_ITEM";

        case SE_CLS_DRM_EDGE_DIRECTION:
             return "SE_CLS_DRM_EDGE_DIRECTION";

        case SE_CLS_DRM_EI_3D_LOCATION:
             return "SE_CLS_DRM_EI_3D_LOCATION";

        case SE_CLS_DRM_ELLIPSE:
             return "SE_CLS_DRM_ELLIPSE";

        case SE_CLS_DRM_EMISSIVE_COLOUR:
             return "SE_CLS_DRM_EMISSIVE_COLOUR";

        case SE_CLS_DRM_ENCLOSING_VOLUME:
             return "SE_CLS_DRM_ENCLOSING_VOLUME";

        case SE_CLS_DRM_ENUMERATION_AXIS:
             return "SE_CLS_DRM_ENUMERATION_AXIS";

        case SE_CLS_DRM_ENVIRONMENT_ROOT:
             return "SE_CLS_DRM_ENVIRONMENT_ROOT";

        case SE_CLS_DRM_ENVIRONMENTAL_DOMAIN_SUMMARY:
             return "SE_CLS_DRM_ENVIRONMENTAL_DOMAIN_SUMMARY";

        case SE_CLS_DRM_EXPRESSION:
             return "SE_CLS_DRM_EXPRESSION";

        case SE_CLS_DRM_FACE_DIRECTION:
             return "SE_CLS_DRM_FACE_DIRECTION";

        case SE_CLS_DRM_FADE_RANGE:
             return "SE_CLS_DRM_FADE_RANGE";

        case SE_CLS_DRM_FEATURE_EDGE:
             return "SE_CLS_DRM_FEATURE_EDGE";

        case SE_CLS_DRM_FEATURE_FACE:
             return "SE_CLS_DRM_FEATURE_FACE";

        case SE_CLS_DRM_FEATURE_FACE_RING:
             return "SE_CLS_DRM_FEATURE_FACE_RING";

        case SE_CLS_DRM_FEATURE_HIERARCHY:
             return "SE_CLS_DRM_FEATURE_HIERARCHY";

        case SE_CLS_DRM_FEATURE_MODEL:
             return "SE_CLS_DRM_FEATURE_MODEL";

        case SE_CLS_DRM_FEATURE_MODEL_INSTANCE:
             return "SE_CLS_DRM_FEATURE_MODEL_INSTANCE";

        case SE_CLS_DRM_FEATURE_NODE:
             return "SE_CLS_DRM_FEATURE_NODE";

        case SE_CLS_DRM_FEATURE_REPRESENTATION:
             return "SE_CLS_DRM_FEATURE_REPRESENTATION";

        case SE_CLS_DRM_FEATURE_TOPOLOGY:
             return "SE_CLS_DRM_FEATURE_TOPOLOGY";

        case SE_CLS_DRM_FEATURE_TOPOLOGY_HIERARCHY:
             return "SE_CLS_DRM_FEATURE_TOPOLOGY_HIERARCHY";

        case SE_CLS_DRM_FEATURE_VOLUME:
             return "SE_CLS_DRM_FEATURE_VOLUME";

        case SE_CLS_DRM_FEATURE_VOLUME_SHELL:
             return "SE_CLS_DRM_FEATURE_VOLUME_SHELL";

        case SE_CLS_DRM_FINITE_ELEMENT_MESH:
             return "SE_CLS_DRM_FINITE_ELEMENT_MESH";

        case SE_CLS_DRM_FLASHING_LIGHT_BEHAVIOUR:
             return "SE_CLS_DRM_FLASHING_LIGHT_BEHAVIOUR";

        case SE_CLS_DRM_FUNCTION:
             return "SE_CLS_DRM_FUNCTION";

        case SE_CLS_DRM_FUNCTIONAL_ASSOCIATION_DATA:
             return "SE_CLS_DRM_FUNCTIONAL_ASSOCIATION_DATA";

        case SE_CLS_DRM_GEOMETRIC_CENTRE:
             return "SE_CLS_DRM_GEOMETRIC_CENTRE";

        case SE_CLS_DRM_GEOMETRY_EDGE:
             return "SE_CLS_DRM_GEOMETRY_EDGE";

        case SE_CLS_DRM_GEOMETRY_FACE:
             return "SE_CLS_DRM_GEOMETRY_FACE";

        case SE_CLS_DRM_GEOMETRY_HIERARCHY:
             return "SE_CLS_DRM_GEOMETRY_HIERARCHY";

        case SE_CLS_DRM_GEOMETRY_MODEL:
             return "SE_CLS_DRM_GEOMETRY_MODEL";

        case SE_CLS_DRM_GEOMETRY_MODEL_INSTANCE:
             return "SE_CLS_DRM_GEOMETRY_MODEL_INSTANCE";

        case SE_CLS_DRM_GEOMETRY_NODE:
             return "SE_CLS_DRM_GEOMETRY_NODE";

        case SE_CLS_DRM_GEOMETRY_REPRESENTATION:
             return "SE_CLS_DRM_GEOMETRY_REPRESENTATION";

        case SE_CLS_DRM_GEOMETRY_TOPOLOGY:
             return "SE_CLS_DRM_GEOMETRY_TOPOLOGY";

        case SE_CLS_DRM_GEOMETRY_TOPOLOGY_HIERARCHY:
             return "SE_CLS_DRM_GEOMETRY_TOPOLOGY_HIERARCHY";

        case SE_CLS_DRM_GEOMETRY_VOLUME:
             return "SE_CLS_DRM_GEOMETRY_VOLUME";

        case SE_CLS_DRM_GRID_OVERLAP:
             return "SE_CLS_DRM_GRID_OVERLAP";

        case SE_CLS_DRM_HAEC_3D_LOCATION:
             return "SE_CLS_DRM_HAEC_3D_LOCATION";

        case SE_CLS_DRM_HEEC_3D_LOCATION:
             return "SE_CLS_DRM_HEEC_3D_LOCATION";

        case SE_CLS_DRM_HEEQ_3D_LOCATION:
             return "SE_CLS_DRM_HEEQ_3D_LOCATION";

        case SE_CLS_DRM_HIERARCHY_DATA:
             return "SE_CLS_DRM_HIERARCHY_DATA";

        case SE_CLS_DRM_HIERARCHY_SUMMARY_ITEM:
             return "SE_CLS_DRM_HIERARCHY_SUMMARY_ITEM";

        case SE_CLS_DRM_HSV_COLOUR:
             return "SE_CLS_DRM_HSV_COLOUR";

        case SE_CLS_DRM_HSV_COLOUR_CONTROL_LINK:
             return "SE_CLS_DRM_HSV_COLOUR_CONTROL_LINK";

        case SE_CLS_DRM_ICON:
             return "SE_CLS_DRM_ICON";

        case SE_CLS_DRM_IDENTIFICATION:
             return "SE_CLS_DRM_IDENTIFICATION";

        case SE_CLS_DRM_IMAGE:
             return "SE_CLS_DRM_IMAGE";

        case SE_CLS_DRM_IMAGE_ANCHOR:
             return "SE_CLS_DRM_IMAGE_ANCHOR";

        case SE_CLS_DRM_IMAGE_LIBRARY:
             return "SE_CLS_DRM_IMAGE_LIBRARY";

        case SE_CLS_DRM_IMAGE_MAPPING_FUNCTION:
             return "SE_CLS_DRM_IMAGE_MAPPING_FUNCTION";

        case SE_CLS_DRM_IN_OUT:
             return "SE_CLS_DRM_IN_OUT";

        case SE_CLS_DRM_INDEX_LOD_DATA:
             return "SE_CLS_DRM_INDEX_LOD_DATA";

        case SE_CLS_DRM_INFINITE_LIGHT:
             return "SE_CLS_DRM_INFINITE_LIGHT";

        case SE_CLS_DRM_INLINE_COLOUR:
             return "SE_CLS_DRM_INLINE_COLOUR";

        case SE_CLS_DRM_INTERFACE_TEMPLATE:
             return "SE_CLS_DRM_INTERFACE_TEMPLATE";

        case SE_CLS_DRM_INTERVAL_AXIS:
             return "SE_CLS_DRM_INTERVAL_AXIS";

        case SE_CLS_DRM_IRREGULAR_AXIS:
             return "SE_CLS_DRM_IRREGULAR_AXIS";

        case SE_CLS_DRM_KEYWORDS:
             return "SE_CLS_DRM_KEYWORDS";

        case SE_CLS_DRM_LABEL:
             return "SE_CLS_DRM_LABEL";

        case SE_CLS_DRM_LCC_AUGMENTED_3D_LOCATION:
             return "SE_CLS_DRM_LCC_AUGMENTED_3D_LOCATION";

        case SE_CLS_DRM_LCC_SURFACE_LOCATION:
             return "SE_CLS_DRM_LCC_SURFACE_LOCATION";

        case SE_CLS_DRM_LCE_3D_LOCATION:
             return "SE_CLS_DRM_LCE_3D_LOCATION";

        case SE_CLS_DRM_LEGAL_CONSTRAINTS:
             return "SE_CLS_DRM_LEGAL_CONSTRAINTS";

        case SE_CLS_DRM_LIBRARY:
             return "SE_CLS_DRM_LIBRARY";

        case SE_CLS_DRM_LIGHT_RENDERING_BEHAVIOUR:
             return "SE_CLS_DRM_LIGHT_RENDERING_BEHAVIOUR";

        case SE_CLS_DRM_LIGHT_RENDERING_PROPERTIES:
             return "SE_CLS_DRM_LIGHT_RENDERING_PROPERTIES";

        case SE_CLS_DRM_LIGHT_RENDERING_PROPERTIES_CONTROL_LINK:
             return "SE_CLS_DRM_LIGHT_RENDERING_PROPERTIES_CONTROL_LINK";

        case SE_CLS_DRM_LIGHT_SOURCE:
             return "SE_CLS_DRM_LIGHT_SOURCE";

        case SE_CLS_DRM_LIGHT_SOURCE_CONTROL_LINK:
             return "SE_CLS_DRM_LIGHT_SOURCE_CONTROL_LINK";

        case SE_CLS_DRM_LINE:
             return "SE_CLS_DRM_LINE";

        case SE_CLS_DRM_LINEAGE:
             return "SE_CLS_DRM_LINEAGE";

        case SE_CLS_DRM_LINEAR_FEATURE:
             return "SE_CLS_DRM_LINEAR_FEATURE";

        case SE_CLS_DRM_LINEAR_GEOMETRY:
             return "SE_CLS_DRM_LINEAR_GEOMETRY";

        case SE_CLS_DRM_LITERAL:
             return "SE_CLS_DRM_LITERAL";

        case SE_CLS_DRM_LOBE_DATA:
             return "SE_CLS_DRM_LOBE_DATA";

        case SE_CLS_DRM_LOCAL_4X4:
             return "SE_CLS_DRM_LOCAL_4X4";

        case SE_CLS_DRM_LOCATION:
             return "SE_CLS_DRM_LOCATION";

        case SE_CLS_DRM_LOCATION_2D:
             return "SE_CLS_DRM_LOCATION_2D";

        case SE_CLS_DRM_LOCATION_3D:
             return "SE_CLS_DRM_LOCATION_3D";

        case SE_CLS_DRM_LOCATION_SURFACE:
             return "SE_CLS_DRM_LOCATION_SURFACE";

        case SE_CLS_DRM_LOD_RELATED_FEATURES:
             return "SE_CLS_DRM_LOD_RELATED_FEATURES";

        case SE_CLS_DRM_LOD_RELATED_GEOMETRY:
             return "SE_CLS_DRM_LOD_RELATED_GEOMETRY";

        case SE_CLS_DRM_LSA_2D_LOCATION:
             return "SE_CLS_DRM_LSA_2D_LOCATION";

        case SE_CLS_DRM_LSP_2D_LOCATION:
             return "SE_CLS_DRM_LSP_2D_LOCATION";

        case SE_CLS_DRM_LSR_2D_LOCATION:
             return "SE_CLS_DRM_LSR_2D_LOCATION";

        case SE_CLS_DRM_LSR_3D_LOCATION:
             return "SE_CLS_DRM_LSR_3D_LOCATION";

        case SE_CLS_DRM_LSR_3D_LOCATION_CONTROL_LINK:
             return "SE_CLS_DRM_LSR_3D_LOCATION_CONTROL_LINK";

        case SE_CLS_DRM_LSR_TRANSFORMATION:
             return "SE_CLS_DRM_LSR_TRANSFORMATION";

        case SE_CLS_DRM_LSR_TRANSFORMATION_STEP:
             return "SE_CLS_DRM_LSR_TRANSFORMATION_STEP";

        case SE_CLS_DRM_LTSAS_3D_LOCATION:
             return "SE_CLS_DRM_LTSAS_3D_LOCATION";

        case SE_CLS_DRM_LTSAS_SURFACE_LOCATION:
             return "SE_CLS_DRM_LTSAS_SURFACE_LOCATION";

        case SE_CLS_DRM_LTSC_3D_LOCATION:
             return "SE_CLS_DRM_LTSC_3D_LOCATION";

        case SE_CLS_DRM_LTSC_SURFACE_LOCATION:
             return "SE_CLS_DRM_LTSC_SURFACE_LOCATION";

        case SE_CLS_DRM_LTSE_3D_LOCATION:
             return "SE_CLS_DRM_LTSE_3D_LOCATION";

        case SE_CLS_DRM_LTSE_SURFACE_LOCATION:
             return "SE_CLS_DRM_LTSE_SURFACE_LOCATION";

        case SE_CLS_DRM_M_AUGMENTED_3D_LOCATION:
             return "SE_CLS_DRM_M_AUGMENTED_3D_LOCATION";

        case SE_CLS_DRM_M_SURFACE_LOCATION:
             return "SE_CLS_DRM_M_SURFACE_LOCATION";

        case SE_CLS_DRM_MAP_SCALE_LOD_DATA:
             return "SE_CLS_DRM_MAP_SCALE_LOD_DATA";

        case SE_CLS_DRM_MESH_FACE_TABLE:
             return "SE_CLS_DRM_MESH_FACE_TABLE";

        case SE_CLS_DRM_MODEL:
             return "SE_CLS_DRM_MODEL";

        case SE_CLS_DRM_MODEL_INSTANCE_TEMPLATE_INDEX:
             return "SE_CLS_DRM_MODEL_INSTANCE_TEMPLATE_INDEX";

        case SE_CLS_DRM_MODEL_LIBRARY:
             return "SE_CLS_DRM_MODEL_LIBRARY";

        case SE_CLS_DRM_MOVING_LIGHT_BEHAVIOUR:
             return "SE_CLS_DRM_MOVING_LIGHT_BEHAVIOUR";

        case SE_CLS_DRM_OCTANT_DATA:
             return "SE_CLS_DRM_OCTANT_DATA";

        case SE_CLS_DRM_OCTANT_RELATED_FEATURES:
             return "SE_CLS_DRM_OCTANT_RELATED_FEATURES";

        case SE_CLS_DRM_OCTANT_RELATED_GEOMETRY:
             return "SE_CLS_DRM_OCTANT_RELATED_GEOMETRY";

        case SE_CLS_DRM_OMS_AUGMENTED_3D_LOCATION:
             return "SE_CLS_DRM_OMS_AUGMENTED_3D_LOCATION";

        case SE_CLS_DRM_OMS_SURFACE_LOCATION:
             return "SE_CLS_DRM_OMS_SURFACE_LOCATION";

        case SE_CLS_DRM_OVERLOAD_PRIORITY_INDEX:
             return "SE_CLS_DRM_OVERLOAD_PRIORITY_INDEX";

        case SE_CLS_DRM_PARALLELEPIPED_VOLUME_EXTENT:
             return "SE_CLS_DRM_PARALLELEPIPED_VOLUME_EXTENT";

        case SE_CLS_DRM_PD_3D_LOCATION:
             return "SE_CLS_DRM_PD_3D_LOCATION";

        case SE_CLS_DRM_PD_SURFACE_LOCATION:
             return "SE_CLS_DRM_PD_SURFACE_LOCATION";

        case SE_CLS_DRM_PERIMETER_DATA:
             return "SE_CLS_DRM_PERIMETER_DATA";

        case SE_CLS_DRM_PERIMETER_RELATED_FEATURE_TOPOLOGY:
             return "SE_CLS_DRM_PERIMETER_RELATED_FEATURE_TOPOLOGY";

        case SE_CLS_DRM_PERIMETER_RELATED_FEATURES:
             return "SE_CLS_DRM_PERIMETER_RELATED_FEATURES";

        case SE_CLS_DRM_PERIMETER_RELATED_GEOMETRY:
             return "SE_CLS_DRM_PERIMETER_RELATED_GEOMETRY";

        case SE_CLS_DRM_PERIMETER_RELATED_GEOMETRY_TOPOLOGY:
             return "SE_CLS_DRM_PERIMETER_RELATED_GEOMETRY_TOPOLOGY";

        case SE_CLS_DRM_POINT:
             return "SE_CLS_DRM_POINT";

        case SE_CLS_DRM_POINT_FEATURE:
             return "SE_CLS_DRM_POINT_FEATURE";

        case SE_CLS_DRM_POLYGON:
             return "SE_CLS_DRM_POLYGON";

        case SE_CLS_DRM_POLYGON_CONTROL_LINK:
             return "SE_CLS_DRM_POLYGON_CONTROL_LINK";

        case SE_CLS_DRM_POLYHEDRON:
             return "SE_CLS_DRM_POLYHEDRON";

        case SE_CLS_DRM_POSITIONAL_LIGHT:
             return "SE_CLS_DRM_POSITIONAL_LIGHT";

        case SE_CLS_DRM_PREDEFINED_FUNCTION:
             return "SE_CLS_DRM_PREDEFINED_FUNCTION";

        case SE_CLS_DRM_PRESENTATION_DOMAIN:
             return "SE_CLS_DRM_PRESENTATION_DOMAIN";

        case SE_CLS_DRM_PRIMITIVE_COLOUR:
             return "SE_CLS_DRM_PRIMITIVE_COLOUR";

        case SE_CLS_DRM_PRIMITIVE_FEATURE:
             return "SE_CLS_DRM_PRIMITIVE_FEATURE";

        case SE_CLS_DRM_PRIMITIVE_GEOMETRY:
             return "SE_CLS_DRM_PRIMITIVE_GEOMETRY";

        case SE_CLS_DRM_PRIMITIVE_SUMMARY_ITEM:
             return "SE_CLS_DRM_PRIMITIVE_SUMMARY_ITEM";

        case SE_CLS_DRM_PROCESS_STEP:
             return "SE_CLS_DRM_PROCESS_STEP";

        case SE_CLS_DRM_PROPERTY:
             return "SE_CLS_DRM_PROPERTY";

        case SE_CLS_DRM_PROPERTY_CHARACTERISTIC:
             return "SE_CLS_DRM_PROPERTY_CHARACTERISTIC";

        case SE_CLS_DRM_PROPERTY_DESCRIPTION:
             return "SE_CLS_DRM_PROPERTY_DESCRIPTION";

        case SE_CLS_DRM_PROPERTY_GRID:
             return "SE_CLS_DRM_PROPERTY_GRID";

        case SE_CLS_DRM_PROPERTY_GRID_HOOK_POINT:
             return "SE_CLS_DRM_PROPERTY_GRID_HOOK_POINT";

        case SE_CLS_DRM_PROPERTY_SET:
             return "SE_CLS_DRM_PROPERTY_SET";

        case SE_CLS_DRM_PROPERTY_SET_INDEX:
             return "SE_CLS_DRM_PROPERTY_SET_INDEX";

        case SE_CLS_DRM_PROPERTY_SET_INDEX_CONTROL_LINK:
             return "SE_CLS_DRM_PROPERTY_SET_INDEX_CONTROL_LINK";

        case SE_CLS_DRM_PROPERTY_SET_TABLE:
             return "SE_CLS_DRM_PROPERTY_SET_TABLE";

        case SE_CLS_DRM_PROPERTY_SET_TABLE_GROUP:
             return "SE_CLS_DRM_PROPERTY_SET_TABLE_GROUP";

        case SE_CLS_DRM_PROPERTY_SET_TABLE_LIBRARY:
             return "SE_CLS_DRM_PROPERTY_SET_TABLE_LIBRARY";

        case SE_CLS_DRM_PROPERTY_TABLE:
             return "SE_CLS_DRM_PROPERTY_TABLE";

        case SE_CLS_DRM_PROPERTY_TABLE_REFERENCE:
             return "SE_CLS_DRM_PROPERTY_TABLE_REFERENCE";

        case SE_CLS_DRM_PROPERTY_TABLE_REFERENCE_CONTROL_LINK:
             return "SE_CLS_DRM_PROPERTY_TABLE_REFERENCE_CONTROL_LINK";

        case SE_CLS_DRM_PROPERTY_VALUE:
             return "SE_CLS_DRM_PROPERTY_VALUE";

        case SE_CLS_DRM_PROXIMITY_DATA:
             return "SE_CLS_DRM_PROXIMITY_DATA";

        case SE_CLS_DRM_PS_AUGMENTED_3D_LOCATION:
             return "SE_CLS_DRM_PS_AUGMENTED_3D_LOCATION";

        case SE_CLS_DRM_PS_SURFACE_LOCATION:
             return "SE_CLS_DRM_PS_SURFACE_LOCATION";

        case SE_CLS_DRM_PSEUDO_CODE_FUNCTION:
             return "SE_CLS_DRM_PSEUDO_CODE_FUNCTION";

        case SE_CLS_DRM_PYRAMID_DIRECTIONAL_LIGHT:
             return "SE_CLS_DRM_PYRAMID_DIRECTIONAL_LIGHT";

        case SE_CLS_DRM_QUADRANT_DATA:
             return "SE_CLS_DRM_QUADRANT_DATA";

        case SE_CLS_DRM_QUADRANT_RELATED_FEATURES:
             return "SE_CLS_DRM_QUADRANT_RELATED_FEATURES";

        case SE_CLS_DRM_QUADRANT_RELATED_GEOMETRY:
             return "SE_CLS_DRM_QUADRANT_RELATED_GEOMETRY";

        case SE_CLS_DRM_REFERENCE_ORIGIN:
             return "SE_CLS_DRM_REFERENCE_ORIGIN";

        case SE_CLS_DRM_REFERENCE_SURFACE:
             return "SE_CLS_DRM_REFERENCE_SURFACE";

        case SE_CLS_DRM_REFERENCE_VECTOR:
             return "SE_CLS_DRM_REFERENCE_VECTOR";

        case SE_CLS_DRM_REFERENCE_VECTOR_CONTROL_LINK:
             return "SE_CLS_DRM_REFERENCE_VECTOR_CONTROL_LINK";

        case SE_CLS_DRM_REGULAR_AXIS:
             return "SE_CLS_DRM_REGULAR_AXIS";

        case SE_CLS_DRM_RELATIVE_TIME:
             return "SE_CLS_DRM_RELATIVE_TIME";

        case SE_CLS_DRM_RELATIVE_TIME_INTERVAL:
             return "SE_CLS_DRM_RELATIVE_TIME_INTERVAL";

        case SE_CLS_DRM_RENDERING_PRIORITY_LEVEL:
             return "SE_CLS_DRM_RENDERING_PRIORITY_LEVEL";

        case SE_CLS_DRM_RENDERING_PROPERTIES:
             return "SE_CLS_DRM_RENDERING_PROPERTIES";

        case SE_CLS_DRM_RESPONSIBLE_PARTY:
             return "SE_CLS_DRM_RESPONSIBLE_PARTY";

        case SE_CLS_DRM_RGB_COLOUR:
             return "SE_CLS_DRM_RGB_COLOUR";

        case SE_CLS_DRM_RGB_COLOUR_CONTROL_LINK:
             return "SE_CLS_DRM_RGB_COLOUR_CONTROL_LINK";

        case SE_CLS_DRM_ROLE_DATA:
             return "SE_CLS_DRM_ROLE_DATA";

        case SE_CLS_DRM_ROTATING_LIGHT_BEHAVIOUR:
             return "SE_CLS_DRM_ROTATING_LIGHT_BEHAVIOUR";

        case SE_CLS_DRM_ROTATION:
             return "SE_CLS_DRM_ROTATION";

        case SE_CLS_DRM_ROTATION_CONTROL_LINK:
             return "SE_CLS_DRM_ROTATION_CONTROL_LINK";

        case SE_CLS_DRM_SCALE:
             return "SE_CLS_DRM_SCALE";

        case SE_CLS_DRM_SCALE_CONTROL_LINK:
             return "SE_CLS_DRM_SCALE_CONTROL_LINK";

        case SE_CLS_DRM_SEASON:
             return "SE_CLS_DRM_SEASON";

        case SE_CLS_DRM_SECURITY_CONSTRAINTS:
             return "SE_CLS_DRM_SECURITY_CONSTRAINTS";

        case SE_CLS_DRM_SEC_3D_LOCATION:
             return "SE_CLS_DRM_SEC_3D_LOCATION";

        case SE_CLS_DRM_SEDRIS_ABSTRACT_BASE:
             return "SE_CLS_DRM_SEDRIS_ABSTRACT_BASE";

        case SE_CLS_DRM_SEPARATING_PLANE:
             return "SE_CLS_DRM_SEPARATING_PLANE";

        case SE_CLS_DRM_SEPARATING_PLANE_DATA:
             return "SE_CLS_DRM_SEPARATING_PLANE_DATA";

        case SE_CLS_DRM_SEPARATING_PLANE_RELATED_GEOMETRY:
             return "SE_CLS_DRM_SEPARATING_PLANE_RELATED_GEOMETRY";

        case SE_CLS_DRM_SEPARATING_PLANE_RELATIONS:
             return "SE_CLS_DRM_SEPARATING_PLANE_RELATIONS";

        case SE_CLS_DRM_SEQ_3D_LOCATION:
             return "SE_CLS_DRM_SEQ_3D_LOCATION";

        case SE_CLS_DRM_SMD_3D_LOCATION:
             return "SE_CLS_DRM_SMD_3D_LOCATION";

        case SE_CLS_DRM_SME_3D_LOCATION:
             return "SE_CLS_DRM_SME_3D_LOCATION";

        case SE_CLS_DRM_SOUND:
             return "SE_CLS_DRM_SOUND";

        case SE_CLS_DRM_SOUND_INSTANCE:
             return "SE_CLS_DRM_SOUND_INSTANCE";

        case SE_CLS_DRM_SOUND_INSTANCE_CONTROL_LINK:
             return "SE_CLS_DRM_SOUND_INSTANCE_CONTROL_LINK";

        case SE_CLS_DRM_SOUND_LIBRARY:
             return "SE_CLS_DRM_SOUND_LIBRARY";

        case SE_CLS_DRM_SOUND_VOLUME:
             return "SE_CLS_DRM_SOUND_VOLUME";

        case SE_CLS_DRM_SOURCE:
             return "SE_CLS_DRM_SOURCE";

        case SE_CLS_DRM_SPATIAL_ASSOCIATION_DATA:
             return "SE_CLS_DRM_SPATIAL_ASSOCIATION_DATA";

        case SE_CLS_DRM_SPATIAL_EXTENT:
             return "SE_CLS_DRM_SPATIAL_EXTENT";

        case SE_CLS_DRM_SPATIAL_INDEX_DATA:
             return "SE_CLS_DRM_SPATIAL_INDEX_DATA";

        case SE_CLS_DRM_SPATIAL_INDEX_RELATED_FEATURE_TOPOLOGY:
             return "SE_CLS_DRM_SPATIAL_INDEX_RELATED_FEATURE_TOPOLOGY";

        case SE_CLS_DRM_SPATIAL_INDEX_RELATED_FEATURES:
             return "SE_CLS_DRM_SPATIAL_INDEX_RELATED_FEATURES";

        case SE_CLS_DRM_SPATIAL_INDEX_RELATED_GEOMETRY:
             return "SE_CLS_DRM_SPATIAL_INDEX_RELATED_GEOMETRY";

        case SE_CLS_DRM_SPATIAL_INDEX_RELATED_GEOMETRY_TOPOLOGY:
             return "SE_CLS_DRM_SPATIAL_INDEX_RELATED_GEOMETRY_TOPOLOGY";

        case SE_CLS_DRM_SPATIAL_RESOLUTION_LOD_DATA:
             return "SE_CLS_DRM_SPATIAL_RESOLUTION_LOD_DATA";

        case SE_CLS_DRM_SPECULAR_COLOUR:
             return "SE_CLS_DRM_SPECULAR_COLOUR";

        case SE_CLS_DRM_SPHERICAL_VOLUME_EXTENT:
             return "SE_CLS_DRM_SPHERICAL_VOLUME_EXTENT";

        case SE_CLS_DRM_SPOT_LIGHT:
             return "SE_CLS_DRM_SPOT_LIGHT";

        case SE_CLS_DRM_SRF_SUMMARY:
             return "SE_CLS_DRM_SRF_SUMMARY";

        case SE_CLS_DRM_STAMP_BEHAVIOUR:
             return "SE_CLS_DRM_STAMP_BEHAVIOUR";

        case SE_CLS_DRM_STATE_CONTROL_LINK:
             return "SE_CLS_DRM_STATE_CONTROL_LINK";

        case SE_CLS_DRM_STATE_DATA:
             return "SE_CLS_DRM_STATE_DATA";

        case SE_CLS_DRM_STATE_RELATED_FEATURES:
             return "SE_CLS_DRM_STATE_RELATED_FEATURES";

        case SE_CLS_DRM_STATE_RELATED_GEOMETRY:
             return "SE_CLS_DRM_STATE_RELATED_GEOMETRY";

        case SE_CLS_DRM_STROBING_LIGHT_BEHAVIOUR:
             return "SE_CLS_DRM_STROBING_LIGHT_BEHAVIOUR";

        case SE_CLS_DRM_SURFACE_GEOMETRY:
             return "SE_CLS_DRM_SURFACE_GEOMETRY";

        case SE_CLS_DRM_SYMBOL:
             return "SE_CLS_DRM_SYMBOL";

        case SE_CLS_DRM_SYMBOL_LIBRARY:
             return "SE_CLS_DRM_SYMBOL_LIBRARY";

        case SE_CLS_DRM_TABLE_PROPERTY_DESCRIPTION:
             return "SE_CLS_DRM_TABLE_PROPERTY_DESCRIPTION";

        case SE_CLS_DRM_TACK_POINT:
             return "SE_CLS_DRM_TACK_POINT";

        case SE_CLS_DRM_TEXT:
             return "SE_CLS_DRM_TEXT";

        case SE_CLS_DRM_TEXTURE_COORDINATE:
             return "SE_CLS_DRM_TEXTURE_COORDINATE";

        case SE_CLS_DRM_TEXTURE_COORDINATE_CONTROL_LINK:
             return "SE_CLS_DRM_TEXTURE_COORDINATE_CONTROL_LINK";

        case SE_CLS_DRM_TIME_CONSTRAINTS_DATA:
             return "SE_CLS_DRM_TIME_CONSTRAINTS_DATA";

        case SE_CLS_DRM_TIME_INTERVAL:
             return "SE_CLS_DRM_TIME_INTERVAL";

        case SE_CLS_DRM_TIME_OF_DAY:
             return "SE_CLS_DRM_TIME_OF_DAY";

        case SE_CLS_DRM_TIME_POINT:
             return "SE_CLS_DRM_TIME_POINT";

        case SE_CLS_DRM_TIME_RELATED_FEATURES:
             return "SE_CLS_DRM_TIME_RELATED_FEATURES";

        case SE_CLS_DRM_TIME_RELATED_GEOMETRY:
             return "SE_CLS_DRM_TIME_RELATED_GEOMETRY";

        case SE_CLS_DRM_TM_AUGMENTED_3D_LOCATION:
             return "SE_CLS_DRM_TM_AUGMENTED_3D_LOCATION";

        case SE_CLS_DRM_TM_SURFACE_LOCATION:
             return "SE_CLS_DRM_TM_SURFACE_LOCATION";

        case SE_CLS_DRM_TRANSFORMATION:
             return "SE_CLS_DRM_TRANSFORMATION";

        case SE_CLS_DRM_TRANSLATION:
             return "SE_CLS_DRM_TRANSLATION";

        case SE_CLS_DRM_TRANSLATION_CONTROL_LINK:
             return "SE_CLS_DRM_TRANSLATION_CONTROL_LINK";

        case SE_CLS_DRM_TRANSLUCENCY:
             return "SE_CLS_DRM_TRANSLUCENCY";

        case SE_CLS_DRM_TRANSLUCENCY_CONTROL_LINK:
             return "SE_CLS_DRM_TRANSLUCENCY_CONTROL_LINK";

        case SE_CLS_DRM_TRANSMITTAL_ROOT:
             return "SE_CLS_DRM_TRANSMITTAL_ROOT";

        case SE_CLS_DRM_TRANSMITTAL_SUMMARY:
             return "SE_CLS_DRM_TRANSMITTAL_SUMMARY";

        case SE_CLS_DRM_TWINKLING_LIGHT_BEHAVIOUR:
             return "SE_CLS_DRM_TWINKLING_LIGHT_BEHAVIOUR";

        case SE_CLS_DRM_UNION_OF_FEATURE_TOPOLOGY:
             return "SE_CLS_DRM_UNION_OF_FEATURE_TOPOLOGY";

        case SE_CLS_DRM_UNION_OF_FEATURES:
             return "SE_CLS_DRM_UNION_OF_FEATURES";

        case SE_CLS_DRM_UNION_OF_GEOMETRY:
             return "SE_CLS_DRM_UNION_OF_GEOMETRY";

        case SE_CLS_DRM_UNION_OF_GEOMETRY_HIERARCHY:
             return "SE_CLS_DRM_UNION_OF_GEOMETRY_HIERARCHY";

        case SE_CLS_DRM_UNION_OF_GEOMETRY_TOPOLOGY:
             return "SE_CLS_DRM_UNION_OF_GEOMETRY_TOPOLOGY";

        case SE_CLS_DRM_UNION_OF_PRIMITIVE_GEOMETRY:
             return "SE_CLS_DRM_UNION_OF_PRIMITIVE_GEOMETRY";

        case SE_CLS_DRM_VARIABLE:
             return "SE_CLS_DRM_VARIABLE";

        case SE_CLS_DRM_VERTEX:
             return "SE_CLS_DRM_VERTEX";

        case SE_CLS_DRM_VOLUME_EXTENT:
             return "SE_CLS_DRM_VOLUME_EXTENT";

        case SE_CLS_DRM_VOLUME_GEOMETRY:
             return "SE_CLS_DRM_VOLUME_GEOMETRY";

        case SE_CLS_DRM_VOLUME_LIGHT_BEHAVIOUR:
             return "SE_CLS_DRM_VOLUME_LIGHT_BEHAVIOUR";

        case SE_CLS_DRM_VOLUME_LOD_DATA:
             return "SE_CLS_DRM_VOLUME_LOD_DATA";

        case SE_CLS_DRM_VOLUME_OBJECT:
             return "SE_CLS_DRM_VOLUME_OBJECT";

        case SE_CLS_DRM_VOLUMETRIC_FEATURE:
             return "SE_CLS_DRM_VOLUMETRIC_FEATURE";

        case SE_CLS_DRM_WORLD_3X3:
             return "SE_CLS_DRM_WORLD_3X3";

        case SE_CLS_DRM_WORLD_TRANSFORMATION:
             return "SE_CLS_DRM_WORLD_TRANSFORMATION";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_DRM_Class VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintDRMClass */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintDRMStatusCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintDRMStatusCode
(
    SE_DRM_Status_Code value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_DRM_STAT_CODE_SUCCESS:
             return "SE_DRM_STAT_CODE_SUCCESS";

        case SE_DRM_STAT_CODE_INVALID_CLASS:
             return "SE_DRM_STAT_CODE_INVALID_CLASS";

        case SE_DRM_STAT_CODE_INVALID_CLASS_FIELD:
             return "SE_DRM_STAT_CODE_INVALID_CLASS_FIELD";

        case SE_DRM_STAT_CODE_INVALID_DEST_COLOUR_MODEL:
             return "SE_DRM_STAT_CODE_INVALID_DEST_COLOUR_MODEL";

        case SE_DRM_STAT_CODE_INVALID_ENUMERANT:
             return "SE_DRM_STAT_CODE_INVALID_ENUMERANT";

        case SE_DRM_STAT_CODE_INVALID_SOURCE_COLOUR:
             return "SE_DRM_STAT_CODE_INVALID_SOURCE_COLOUR";

        case SE_DRM_STAT_CODE_INVALID_TYPE:
             return "SE_DRM_STAT_CODE_INVALID_TYPE";

        case SE_DRM_STAT_CODE_INVALID_TYPE_CLASSIFICATION:
             return "SE_DRM_STAT_CODE_INVALID_TYPE_CLASSIFICATION";

        case SE_DRM_STAT_CODE_INVALID_TYPE_FIELD:
             return "SE_DRM_STAT_CODE_INVALID_TYPE_FIELD";

        case SE_DRM_STAT_CODE_INVALID_VERSION:
             return "SE_DRM_STAT_CODE_INVALID_VERSION";

        case SE_DRM_STAT_CODE_NULL_REQUIRED_PARAMETER:
             return "SE_DRM_STAT_CODE_NULL_REQUIRED_PARAMETER";

        case SE_DRM_STAT_CODE_FAILURE:
             return "SE_DRM_STAT_CODE_FAILURE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_DRM_Status_Code VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintDRMStatusCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintDRMType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintDRMType
(
    SE_DRM_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_DRM_TYP_NULL:
             return "SE_DRM_TYP_NULL";

        case SE_DRM_TYP_SE_ADDRESS:
             return "SE_DRM_TYP_SE_ADDRESS";

        case SE_DRM_TYP_SE_API:
             return "SE_DRM_TYP_SE_API";

        case SE_DRM_TYP_EDCS_ATTRIBUTE_CODE:
             return "SE_DRM_TYP_EDCS_ATTRIBUTE_CODE";

        case SE_DRM_TYP_EDCS_ATTRIBUTE_DICTIONARY_ENTRY:
             return "SE_DRM_TYP_EDCS_ATTRIBUTE_DICTIONARY_ENTRY";

        case SE_DRM_TYP_EDCS_ATTRIBUTE_LABEL:
             return "SE_DRM_TYP_EDCS_ATTRIBUTE_LABEL";

        case SE_DRM_TYP_EDCS_ATTRIBUTE_VALUE:
             return "SE_DRM_TYP_EDCS_ATTRIBUTE_VALUE";

        case SE_DRM_TYP_EDCS_ATTRIBUTE_VALUE_TYPE:
             return "SE_DRM_TYP_EDCS_ATTRIBUTE_VALUE_TYPE";

        case SE_DRM_TYP_SE_AXIS_ALIGNMENT:
             return "SE_DRM_TYP_SE_AXIS_ALIGNMENT";

        case SE_DRM_TYP_SRM_AXIS_DIRECTION:
             return "SE_DRM_TYP_SRM_AXIS_DIRECTION";

        case SE_DRM_TYP_EDCS_BOOLEAN:
             return "SE_DRM_TYP_EDCS_BOOLEAN";

        case SE_DRM_TYP_SE_BOOLEAN:
             return "SE_DRM_TYP_SE_BOOLEAN";

        case SE_DRM_TYP_SRM_BOOLEAN:
             return "SE_DRM_TYP_SRM_BOOLEAN";

        case SE_DRM_TYP_SE_BYTE:
             return "SE_DRM_TYP_SE_BYTE";

        case SE_DRM_TYP_SE_BYTE_POSITIVE:
             return "SE_DRM_TYP_SE_BYTE_POSITIVE";

        case SE_DRM_TYP_SE_BYTE_UNSIGNED:
             return "SE_DRM_TYP_SE_BYTE_UNSIGNED";

        case SE_DRM_TYP_SE_CAMERA_PROJECTION_TYPE:
             return "SE_DRM_TYP_SE_CAMERA_PROJECTION_TYPE";

        case SE_DRM_TYP_SRM_CD_3D_COORDINATE:
             return "SE_DRM_TYP_SRM_CD_3D_COORDINATE";

        case SE_DRM_TYP_SRM_CD_SURFACE_COORDINATE:
             return "SE_DRM_TYP_SRM_CD_SURFACE_COORDINATE";

        case SE_DRM_TYP_EDCS_CHARACTER:
             return "SE_DRM_TYP_EDCS_CHARACTER";

        case SE_DRM_TYP_SE_CHARACTER:
             return "SE_DRM_TYP_SE_CHARACTER";

        case SE_DRM_TYP_SE_CI_ONLINEFUNCTIONCODE:
             return "SE_DRM_TYP_SE_CI_ONLINEFUNCTIONCODE";

        case SE_DRM_TYP_SE_CI_ONLINERESOURCE:
             return "SE_DRM_TYP_SE_CI_ONLINERESOURCE";

        case SE_DRM_TYP_SE_CI_ROLECODE:
             return "SE_DRM_TYP_SE_CI_ROLECODE";

        case SE_DRM_TYP_EDCS_CLASSIFICATION_CODE:
             return "SE_DRM_TYP_EDCS_CLASSIFICATION_CODE";

        case SE_DRM_TYP_EDCS_CLASSIFICATION_DICTIONARY_ENTRY:
             return "SE_DRM_TYP_EDCS_CLASSIFICATION_DICTIONARY_ENTRY";

        case SE_DRM_TYP_EDCS_CLASSIFICATION_LABEL:
             return "SE_DRM_TYP_EDCS_CLASSIFICATION_LABEL";

        case SE_DRM_TYP_SE_CMY_DATA:
             return "SE_DRM_TYP_SE_CMY_DATA";

        case SE_DRM_TYP_SE_CMYK_DATA:
             return "SE_DRM_TYP_SE_CMYK_DATA";

        case SE_DRM_TYP_SE_COLOUR_BINDING:
             return "SE_DRM_TYP_SE_COLOUR_BINDING";

        case SE_DRM_TYP_SE_COLOUR_DATA:
             return "SE_DRM_TYP_SE_COLOUR_DATA";

        case SE_DRM_TYP_SE_COLOUR_MAPPING:
             return "SE_DRM_TYP_SE_COLOUR_MAPPING";

        case SE_DRM_TYP_SE_COLOUR_MODEL:
             return "SE_DRM_TYP_SE_COLOUR_MODEL";

        case SE_DRM_TYP_EDCS_CONCEPT_STATUS:
             return "SE_DRM_TYP_EDCS_CONCEPT_STATUS";

        case SE_DRM_TYP_SE_CONTACT_INFORMATION:
             return "SE_DRM_TYP_SE_CONTACT_INFORMATION";

        case SE_DRM_TYP_SRM_COORDINATE:
             return "SE_DRM_TYP_SRM_COORDINATE";

        case SE_DRM_TYP_SRM_COORDINATE2D_ARRAY:
             return "SE_DRM_TYP_SRM_COORDINATE2D_ARRAY";

        case SE_DRM_TYP_SRM_COORDINATE3D_ARRAY:
             return "SE_DRM_TYP_SRM_COORDINATE3D_ARRAY";

        case SE_DRM_TYP_SRM_COORDINATE_VALID_REGION:
             return "SE_DRM_TYP_SRM_COORDINATE_VALID_REGION";

        case SE_DRM_TYP_SRM_COORDINATE_VALID_REGION_ARRAY:
             return "SE_DRM_TYP_SRM_COORDINATE_VALID_REGION_ARRAY";

        case SE_DRM_TYP_EDCS_COUNT:
             return "SE_DRM_TYP_EDCS_COUNT";

        case SE_DRM_TYP_EDCS_COUNT_INTERVAL:
             return "SE_DRM_TYP_EDCS_COUNT_INTERVAL";

        case SE_DRM_TYP_SE_COUNT_INTERVAL_VALUE:
             return "SE_DRM_TYP_SE_COUNT_INTERVAL_VALUE";

        case SE_DRM_TYP_EDCS_COUNT_VALUE:
             return "SE_DRM_TYP_EDCS_COUNT_VALUE";

        case SE_DRM_TYP_SRM_CS_CODE:
             return "SE_DRM_TYP_SRM_CS_CODE";

        case SE_DRM_TYP_SE_DATA_QUALITY_ELEMENT:
             return "SE_DRM_TYP_SE_DATA_QUALITY_ELEMENT";

        case SE_DRM_TYP_SE_DATA_TABLE_DATA:
             return "SE_DRM_TYP_SE_DATA_TABLE_DATA";

        case SE_DRM_TYP_SE_DATA_TABLE_DATA_VALUE_TYPE:
             return "SE_DRM_TYP_SE_DATA_TABLE_DATA_VALUE_TYPE";

        case SE_DRM_TYP_EDCS_DICTIONARY_TYPE:
             return "SE_DRM_TYP_EDCS_DICTIONARY_TYPE";

        case SE_DRM_TYP_SRM_DIRECTION_ARRAY:
             return "SE_DRM_TYP_SRM_DIRECTION_ARRAY";

        case SE_DRM_TYP_SE_DISPLAY_SIDE:
             return "SE_DRM_TYP_SE_DISPLAY_SIDE";

        case SE_DRM_TYP_SE_DISPLAY_STYLE:
             return "SE_DRM_TYP_SE_DISPLAY_STYLE";

        case SE_DRM_TYP_SE_DRM_CLASS:
             return "SE_DRM_TYP_SE_DRM_CLASS";

        case SE_DRM_TYP_SE_DRM_STATUS_CODE:
             return "SE_DRM_TYP_SE_DRM_STATUS_CODE";

        case SE_DRM_TYP_SE_DRM_TYPE:
             return "SE_DRM_TYP_SE_DRM_TYPE";

        case SE_DRM_TYP_SRM_DSS_CODE:
             return "SE_DRM_TYP_SRM_DSS_CODE";

        case SE_DRM_TYP_SRM_EC_PARAMETERS:
             return "SE_DRM_TYP_SRM_EC_PARAMETERS";

        case SE_DRM_TYP_SRM_EI_3D_COORDINATE:
             return "SE_DRM_TYP_SRM_EI_3D_COORDINATE";

        case SE_DRM_TYP_SE_ELEMENT_TYPE:
             return "SE_DRM_TYP_SE_ELEMENT_TYPE";

        case SE_DRM_TYP_SE_ELEMENT_TYPE_CODE:
             return "SE_DRM_TYP_SE_ELEMENT_TYPE_CODE";

        case SE_DRM_TYP_EDCS_ENUMERANT_CODE:
             return "SE_DRM_TYP_EDCS_ENUMERANT_CODE";

        case SE_DRM_TYP_EDCS_ENUMERANT_DICTIONARY_ENTRY:
             return "SE_DRM_TYP_EDCS_ENUMERANT_DICTIONARY_ENTRY";

        case SE_DRM_TYP_EDCS_ENUMERANT_LABEL:
             return "SE_DRM_TYP_EDCS_ENUMERANT_LABEL";

        case SE_DRM_TYP_SE_ENUMERANT_STRUCTURE:
             return "SE_DRM_TYP_SE_ENUMERANT_STRUCTURE";

        case SE_DRM_TYP_SRM_EUCLIDEAN_2D_COORDINATE:
             return "SE_DRM_TYP_SRM_EUCLIDEAN_2D_COORDINATE";

        case SE_DRM_TYP_SRM_EUCLIDEAN_3D_COORDINATE:
             return "SE_DRM_TYP_SRM_EUCLIDEAN_3D_COORDINATE";

        case SE_DRM_TYP_SE_FEATURE_TOPOLOGY_LEVEL:
             return "SE_DRM_TYP_SE_FEATURE_TOPOLOGY_LEVEL";

        case SE_DRM_TYP_SE_FIELD_MODIFIER:
             return "SE_DRM_TYP_SE_FIELD_MODIFIER";

        case SE_DRM_TYP_SE_FLOAT:
             return "SE_DRM_TYP_SE_FLOAT";

        case SE_DRM_TYP_SE_FONT_STYLE:
             return "SE_DRM_TYP_SE_FONT_STYLE";

        case SE_DRM_TYP_SE_FUNCTIONAL_ASSOCIATION_MEANING_TYPE:
             return "SE_DRM_TYP_SE_FUNCTIONAL_ASSOCIATION_MEANING_TYPE";

        case SE_DRM_TYP_SE_GEOMETRIC_CENTRE_CODE:
             return "SE_DRM_TYP_SE_GEOMETRIC_CENTRE_CODE";

        case SE_DRM_TYP_SE_GEOMETRY_TOPOLOGY_LEVEL:
             return "SE_DRM_TYP_SE_GEOMETRY_TOPOLOGY_LEVEL";

        case SE_DRM_TYP_SE_GRID_OVERLAP_OPERATOR:
             return "SE_DRM_TYP_SE_GRID_OVERLAP_OPERATOR";

        case SE_DRM_TYP_EDCS_GROUP_CODE:
             return "SE_DRM_TYP_EDCS_GROUP_CODE";

        case SE_DRM_TYP_EDCS_GROUP_DICTIONARY_ENTRY:
             return "SE_DRM_TYP_EDCS_GROUP_DICTIONARY_ENTRY";

        case SE_DRM_TYP_EDCS_GROUP_LABEL:
             return "SE_DRM_TYP_EDCS_GROUP_LABEL";

        case SE_DRM_TYP_EDCS_GROUP_PAIR:
             return "SE_DRM_TYP_EDCS_GROUP_PAIR";

        case SE_DRM_TYP_SE_HLS_DATA:
             return "SE_DRM_TYP_SE_HLS_DATA";

        case SE_DRM_TYP_SE_HS_MULTIPLICITY_CODE:
             return "SE_DRM_TYP_SE_HS_MULTIPLICITY_CODE";

        case SE_DRM_TYP_SE_HSV_DATA:
             return "SE_DRM_TYP_SE_HSV_DATA";

        case SE_DRM_TYP_SE_IMAGE_COMPONENT_TYPE:
             return "SE_DRM_TYP_SE_IMAGE_COMPONENT_TYPE";

        case SE_DRM_TYP_SE_IMAGE_MAPPING_METHOD:
             return "SE_DRM_TYP_SE_IMAGE_MAPPING_METHOD";

        case SE_DRM_TYP_SE_IMAGE_MIP_EXTENTS:
             return "SE_DRM_TYP_SE_IMAGE_MIP_EXTENTS";

        case SE_DRM_TYP_SE_IMAGE_PROJECTION_TYPE:
             return "SE_DRM_TYP_SE_IMAGE_PROJECTION_TYPE";

        case SE_DRM_TYP_SE_IMAGE_SCAN_DIRECTION:
             return "SE_DRM_TYP_SE_IMAGE_SCAN_DIRECTION";

        case SE_DRM_TYP_SE_IMAGE_SCAN_DIRECTION_Z:
             return "SE_DRM_TYP_SE_IMAGE_SCAN_DIRECTION_Z";

        case SE_DRM_TYP_SE_IMAGE_SIGNATURE:
             return "SE_DRM_TYP_SE_IMAGE_SIGNATURE";

        case SE_DRM_TYP_SE_IMAGE_WRAP:
             return "SE_DRM_TYP_SE_IMAGE_WRAP";

        case SE_DRM_TYP_SE_INDEX_CODE:
             return "SE_DRM_TYP_SE_INDEX_CODE";

        case SE_DRM_TYP_EDCS_INTEGER:
             return "SE_DRM_TYP_EDCS_INTEGER";

        case SE_DRM_TYP_SE_INTEGER:
             return "SE_DRM_TYP_SE_INTEGER";

        case SE_DRM_TYP_SRM_INTEGER:
             return "SE_DRM_TYP_SRM_INTEGER";

        case SE_DRM_TYP_EDCS_INTEGER_INTERVAL:
             return "SE_DRM_TYP_EDCS_INTEGER_INTERVAL";

        case SE_DRM_TYP_SE_INTEGER_INTERVAL_VALUE:
             return "SE_DRM_TYP_SE_INTEGER_INTERVAL_VALUE";

        case SE_DRM_TYP_SRM_INTEGER_POSITIVE:
             return "SE_DRM_TYP_SRM_INTEGER_POSITIVE";

        case SE_DRM_TYP_SE_INTEGER_POSITIVE:
             return "SE_DRM_TYP_SE_INTEGER_POSITIVE";

        case SE_DRM_TYP_SRM_INTEGER_UNSIGNED:
             return "SE_DRM_TYP_SRM_INTEGER_UNSIGNED";

        case SE_DRM_TYP_SE_INTEGER_UNSIGNED:
             return "SE_DRM_TYP_SE_INTEGER_UNSIGNED";

        case SE_DRM_TYP_EDCS_INTEGER_VALUE:
             return "SE_DRM_TYP_EDCS_INTEGER_VALUE";

        case SE_DRM_TYP_SE_INTERPOLATION_TYPE:
             return "SE_DRM_TYP_SE_INTERPOLATION_TYPE";

        case SE_DRM_TYP_SRM_INTERVAL_TYPE:
             return "SE_DRM_TYP_SRM_INTERVAL_TYPE";

        case SE_DRM_TYP_SE_INTERVAL_TYPE:
             return "SE_DRM_TYP_SE_INTERVAL_TYPE";

        case SE_DRM_TYP_SE_INTERVAL_VALUE:
             return "SE_DRM_TYP_SE_INTERVAL_VALUE";

        case SE_DRM_TYP_SE_INTERVAL_VALUE_TYPE:
             return "SE_DRM_TYP_SE_INTERVAL_VALUE_TYPE";

        case SE_DRM_TYP_EDCS_ISO_3166_ENTRY:
             return "SE_DRM_TYP_EDCS_ISO_3166_ENTRY";

        case SE_DRM_TYP_EDCS_ISO_639_ENTRY:
             return "SE_DRM_TYP_EDCS_ISO_639_ENTRY";

        case SE_DRM_TYP_SRM_LCC_PARAMETERS:
             return "SE_DRM_TYP_SRM_LCC_PARAMETERS";

        case SE_DRM_TYP_SRM_LCE_3D_PARAMETERS:
             return "SE_DRM_TYP_SRM_LCE_3D_PARAMETERS";

        case SE_DRM_TYP_EDCS_LOCALE:
             return "SE_DRM_TYP_EDCS_LOCALE";

        case SE_DRM_TYP_SE_LOCALE:
             return "SE_DRM_TYP_SE_LOCALE";

        case SE_DRM_TYP_SRM_LOCAL_TANGENT_PARAMETERS:
             return "SE_DRM_TYP_SRM_LOCAL_TANGENT_PARAMETERS";

        case SE_DRM_TYP_SE_LOD_DATA_TYPE:
             return "SE_DRM_TYP_SE_LOD_DATA_TYPE";

        case SE_DRM_TYP_EDCS_LONG_FLOAT:
             return "SE_DRM_TYP_EDCS_LONG_FLOAT";

        case SE_DRM_TYP_SE_LONG_FLOAT:
             return "SE_DRM_TYP_SE_LONG_FLOAT";

        case SE_DRM_TYP_SRM_LONG_FLOAT:
             return "SE_DRM_TYP_SRM_LONG_FLOAT";

        case SE_DRM_TYP_EDCS_LONG_FLOAT_INTERVAL:
             return "SE_DRM_TYP_EDCS_LONG_FLOAT_INTERVAL";

        case SE_DRM_TYP_SE_LONG_FLOAT_INTERVAL_VALUE:
             return "SE_DRM_TYP_SE_LONG_FLOAT_INTERVAL_VALUE";

        case SE_DRM_TYP_EDCS_LONG_FLOAT_VALUE:
             return "SE_DRM_TYP_EDCS_LONG_FLOAT_VALUE";

        case SE_DRM_TYP_SE_LONG_FLOAT_VALUE:
             return "SE_DRM_TYP_SE_LONG_FLOAT_VALUE";

        case SE_DRM_TYP_SRM_LSA_2D_COORDINATE:
             return "SE_DRM_TYP_SRM_LSA_2D_COORDINATE";

        case SE_DRM_TYP_SRM_LSP_2D_COORDINATE:
             return "SE_DRM_TYP_SRM_LSP_2D_COORDINATE";

        case SE_DRM_TYP_SRM_LSR_2D_PARAMETERS:
             return "SE_DRM_TYP_SRM_LSR_2D_PARAMETERS";

        case SE_DRM_TYP_SRM_LSR_3D_PARAMETERS:
             return "SE_DRM_TYP_SRM_LSR_3D_PARAMETERS";

        case SE_DRM_TYP_SE_LSR_TRANSFORMATION_AXIS:
             return "SE_DRM_TYP_SE_LSR_TRANSFORMATION_AXIS";

        case SE_DRM_TYP_SRM_LTSAS_3D_COORDINATE:
             return "SE_DRM_TYP_SRM_LTSAS_3D_COORDINATE";

        case SE_DRM_TYP_SRM_LTSAS_SURFACE_COORDINATE:
             return "SE_DRM_TYP_SRM_LTSAS_SURFACE_COORDINATE";

        case SE_DRM_TYP_SRM_LTSC_3D_COORDINATE:
             return "SE_DRM_TYP_SRM_LTSC_3D_COORDINATE";

        case SE_DRM_TYP_SRM_LTSC_SURFACE_COORDINATE:
             return "SE_DRM_TYP_SRM_LTSC_SURFACE_COORDINATE";

        case SE_DRM_TYP_SRM_LTSE_3D_COORDINATE:
             return "SE_DRM_TYP_SRM_LTSE_3D_COORDINATE";

        case SE_DRM_TYP_SRM_LTSE_PARAMETERS:
             return "SE_DRM_TYP_SRM_LTSE_PARAMETERS";

        case SE_DRM_TYP_SRM_LTSE_SURFACE_COORDINATE:
             return "SE_DRM_TYP_SRM_LTSE_SURFACE_COORDINATE";

        case SE_DRM_TYP_SRM_MAP_PROJECTION_3D_COORDINATE:
             return "SE_DRM_TYP_SRM_MAP_PROJECTION_3D_COORDINATE";

        case SE_DRM_TYP_SRM_MAP_PROJECTION_SURFACE_COORDINATE:
             return "SE_DRM_TYP_SRM_MAP_PROJECTION_SURFACE_COORDINATE";

        case SE_DRM_TYP_SRM_MATRIX_3X3:
             return "SE_DRM_TYP_SRM_MATRIX_3X3";

        case SE_DRM_TYP_SRM_MATRIX_4X4:
             return "SE_DRM_TYP_SRM_MATRIX_4X4";

        case SE_DRM_TYP_SE_MD_CLASSIFICATIONCODE:
             return "SE_DRM_TYP_SE_MD_CLASSIFICATIONCODE";

        case SE_DRM_TYP_SE_MD_KEYWORDTYPECODE:
             return "SE_DRM_TYP_SE_MD_KEYWORDTYPECODE";

        case SE_DRM_TYP_SE_MD_RESTRICTIONCODE:
             return "SE_DRM_TYP_SE_MD_RESTRICTIONCODE";

        case SE_DRM_TYP_SE_MEDIA_FORMAT:
             return "SE_DRM_TYP_SE_MEDIA_FORMAT";

        case SE_DRM_TYP_SRM_M_PARAMETERS:
             return "SE_DRM_TYP_SRM_M_PARAMETERS";

        case SE_DRM_TYP_SE_MODEL_REFERENCE_TYPE:
             return "SE_DRM_TYP_SE_MODEL_REFERENCE_TYPE";

        case SE_DRM_TYP_SE_MONTH:
             return "SE_DRM_TYP_SE_MONTH";

        case SE_DRM_TYP_SE_MULTIPLICITY:
             return "SE_DRM_TYP_SE_MULTIPLICITY";

        case SE_DRM_TYP_EDCS_NULL:
             return "SE_DRM_TYP_EDCS_NULL";

        case SE_DRM_TYP_EDCS_NUMERIC_VALUE_TYPE:
             return "SE_DRM_TYP_EDCS_NUMERIC_VALUE_TYPE";

        case SE_DRM_TYP_SRM_OBJECT_REFERENCE:
             return "SE_DRM_TYP_SRM_OBJECT_REFERENCE";

        case SE_DRM_TYP_SRM_OBLIQUE_MERCATOR_PARAMETERS:
             return "SE_DRM_TYP_SRM_OBLIQUE_MERCATOR_PARAMETERS";

        case SE_DRM_TYP_SE_OCTANT:
             return "SE_DRM_TYP_SE_OCTANT";

        case SE_DRM_TYP_SE_OCTET:
             return "SE_DRM_TYP_SE_OCTET";

        case SE_DRM_TYP_SE_ORDERING_REASON:
             return "SE_DRM_TYP_SE_ORDERING_REASON";

        case SE_DRM_TYP_EDCS_ORGANIZATION_SCHEMA_CODE:
             return "SE_DRM_TYP_EDCS_ORGANIZATION_SCHEMA_CODE";

        case SE_DRM_TYP_EDCS_ORGANIZATION_SCHEMA_DICTIONARY_ENTRY:
             return "SE_DRM_TYP_EDCS_ORGANIZATION_SCHEMA_DICTIONARY_ENTRY";

        case SE_DRM_TYP_EDCS_ORGANIZATION_SCHEMA_LABEL:
             return "SE_DRM_TYP_EDCS_ORGANIZATION_SCHEMA_LABEL";

        case SE_DRM_TYP_SRM_ORM_CODE:
             return "SE_DRM_TYP_SRM_ORM_CODE";

        case SE_DRM_TYP_SRM_ORM_TRANSFORMATION_2D_PARAMETERS:
             return "SE_DRM_TYP_SRM_ORM_TRANSFORMATION_2D_PARAMETERS";

        case SE_DRM_TYP_SRM_ORM_TRANSFORMATION_3D_PARAMETERS:
             return "SE_DRM_TYP_SRM_ORM_TRANSFORMATION_3D_PARAMETERS";

        case SE_DRM_TYP_SRM_ORMT_CODE:
             return "SE_DRM_TYP_SRM_ORMT_CODE";

        case SE_DRM_TYP_SRM_PD_3D_COORDINATE:
             return "SE_DRM_TYP_SRM_PD_3D_COORDINATE";

        case SE_DRM_TYP_SRM_PD_SURFACE_COORDINATE:
             return "SE_DRM_TYP_SRM_PD_SURFACE_COORDINATE";

        case SE_DRM_TYP_SE_PIXEL_FILL_METHOD:
             return "SE_DRM_TYP_SE_PIXEL_FILL_METHOD";

        case SE_DRM_TYP_SE_POINT_LIGHT_DISPLAY_TYPE:
             return "SE_DRM_TYP_SE_POINT_LIGHT_DISPLAY_TYPE";

        case SE_DRM_TYP_SRM_POLAR_ASPECT:
             return "SE_DRM_TYP_SRM_POLAR_ASPECT";

        case SE_DRM_TYP_SE_POLYGON_FLAG:
             return "SE_DRM_TYP_SE_POLYGON_FLAG";

        case SE_DRM_TYP_SE_PREDEF_FUNC_ARG_STRUCTURE:
             return "SE_DRM_TYP_SE_PREDEF_FUNC_ARG_STRUCTURE";

        case SE_DRM_TYP_SE_PREDEF_FUNC_STRUCTURE:
             return "SE_DRM_TYP_SE_PREDEF_FUNC_STRUCTURE";

        case SE_DRM_TYP_SE_PREDEFINED_FUNCTION:
             return "SE_DRM_TYP_SE_PREDEFINED_FUNCTION";

        case SE_DRM_TYP_SE_PRESENT_IN:
             return "SE_DRM_TYP_SE_PRESENT_IN";

        case SE_DRM_TYP_SE_PRESENTATION_DOMAIN:
             return "SE_DRM_TYP_SE_PRESENTATION_DOMAIN";

        case SE_DRM_TYP_SE_PROPERTY_CODE:
             return "SE_DRM_TYP_SE_PROPERTY_CODE";

        case SE_DRM_TYP_SE_PROPERTY_CODE_TYPE:
             return "SE_DRM_TYP_SE_PROPERTY_CODE_TYPE";

        case SE_DRM_TYP_SRM_PS_PARAMETERS:
             return "SE_DRM_TYP_SRM_PS_PARAMETERS";

        case SE_DRM_TYP_SE_QUADRANT:
             return "SE_DRM_TYP_SE_QUADRANT";

        case SE_DRM_TYP_SRM_RD_CODE:
             return "SE_DRM_TYP_SRM_RD_CODE";

        case SE_DRM_TYP_EDCS_REAL_VALUE:
             return "SE_DRM_TYP_EDCS_REAL_VALUE";

        case SE_DRM_TYP_EDCS_REFERENCE_TYPE:
             return "SE_DRM_TYP_EDCS_REFERENCE_TYPE";

        case SE_DRM_TYP_SE_REFERENCE_VECTOR_TYPE:
             return "SE_DRM_TYP_SE_REFERENCE_VECTOR_TYPE";

        case SE_DRM_TYP_SE_RGB_DATA:
             return "SE_DRM_TYP_SE_RGB_DATA";

        case SE_DRM_TYP_SE_ROTATION_DATA:
             return "SE_DRM_TYP_SE_ROTATION_DATA";

        case SE_DRM_TYP_SE_REFERENCE_SURFACE_ELEVATION_SELECT:
             return "SE_DRM_TYP_SE_REFERENCE_SURFACE_ELEVATION_SELECT";

        case SE_DRM_TYP_SE_REFERENCE_SURFACE_LOD_SELECT:
             return "SE_DRM_TYP_SE_REFERENCE_SURFACE_LOD_SELECT";

        case SE_DRM_TYP_SRM_RT_CODE:
             return "SE_DRM_TYP_SRM_RT_CODE";

        case SE_DRM_TYP_SE_SEASON:
             return "SE_DRM_TYP_SE_SEASON";

        case SE_DRM_TYP_SE_SHADING_METHOD:
             return "SE_DRM_TYP_SE_SHADING_METHOD";

        case SE_DRM_TYP_SE_SHORT_INTEGER:
             return "SE_DRM_TYP_SE_SHORT_INTEGER";

        case SE_DRM_TYP_SE_SHORT_INTEGER_POSITIVE:
             return "SE_DRM_TYP_SE_SHORT_INTEGER_POSITIVE";

        case SE_DRM_TYP_SE_SHORT_INTEGER_UNSIGNED:
             return "SE_DRM_TYP_SE_SHORT_INTEGER_UNSIGNED";

        case SE_DRM_TYP_SE_SINGLE_VALUE:
             return "SE_DRM_TYP_SE_SINGLE_VALUE";

        case SE_DRM_TYP_SE_SINGLE_VALUE_TYPE:
             return "SE_DRM_TYP_SE_SINGLE_VALUE_TYPE";

        case SE_DRM_TYP_SE_SOUND_FORMAT:
             return "SE_DRM_TYP_SE_SOUND_FORMAT";

        case SE_DRM_TYP_SE_SPACING_TYPE:
             return "SE_DRM_TYP_SE_SPACING_TYPE";

        case SE_DRM_TYP_SE_SPATIAL_ASSOCIATION_MEANING_TYPE:
             return "SE_DRM_TYP_SE_SPATIAL_ASSOCIATION_MEANING_TYPE";

        case SE_DRM_TYP_SRM_SPATIAL_COORDINATE_CODE:
             return "SE_DRM_TYP_SRM_SPATIAL_COORDINATE_CODE";

        case SE_DRM_TYP_SE_SPATIAL_INDEX_SPACING_UNIT:
             return "SE_DRM_TYP_SE_SPATIAL_INDEX_SPACING_UNIT";

        case SE_DRM_TYP_SRM_SPHERICAL_3D_COORDINATE:
             return "SE_DRM_TYP_SRM_SPHERICAL_3D_COORDINATE";

        case SE_DRM_TYP_SRM_SRF_CODE:
             return "SE_DRM_TYP_SRM_SRF_CODE";

        case SE_DRM_TYP_SE_SRF_CONTEXT_INFO:
             return "SE_DRM_TYP_SE_SRF_CONTEXT_INFO";

        case SE_DRM_TYP_SRM_SRF_PARAMETERS_INFO:
             return "SE_DRM_TYP_SRM_SRF_PARAMETERS_INFO";

        case SE_DRM_TYP_SRM_SRF_PARAMETERS_INFO_CODE:
             return "SE_DRM_TYP_SRM_SRF_PARAMETERS_INFO_CODE";

        case SE_DRM_TYP_SRM_SRF_REFERENCE_SURFACE_INFO:
             return "SE_DRM_TYP_SRM_SRF_REFERENCE_SURFACE_INFO";

        case SE_DRM_TYP_SRM_SRFS_CODE:
             return "SE_DRM_TYP_SRM_SRFS_CODE";

        case SE_DRM_TYP_SRM_SRFS_CODE_INFO:
             return "SE_DRM_TYP_SRM_SRFS_CODE_INFO";

        case SE_DRM_TYP_SRM_SRFS_INFO:
             return "SE_DRM_TYP_SRM_SRFS_INFO";

        case SE_DRM_TYP_SRM_SRFSM_ALABAMA_SPCS_CODE:
             return "SE_DRM_TYP_SRM_SRFSM_ALABAMA_SPCS_CODE";

        case SE_DRM_TYP_SRM_SRFSM_GTRS_GCS_CODE:
             return "SE_DRM_TYP_SRM_SRFSM_GTRS_GCS_CODE";

        case SE_DRM_TYP_SRM_SRFSM_JAPAN_RECTANGULAR_PLANE_CS_CODE:
             return "SE_DRM_TYP_SRM_SRFSM_JAPAN_RECTANGULAR_PLANE_CS_CODE";

        case SE_DRM_TYP_SRM_SRFSM_LAMBERT_NTF_CODE:
             return "SE_DRM_TYP_SRM_SRFSM_LAMBERT_NTF_CODE";

        case SE_DRM_TYP_SRM_SRFSM_UPS_CODE:
             return "SE_DRM_TYP_SRM_SRFSM_UPS_CODE";

        case SE_DRM_TYP_SRM_SRFSM_UTM_CODE:
             return "SE_DRM_TYP_SRM_SRFSM_UTM_CODE";

        case SE_DRM_TYP_SRM_SRFSM_WISCONSIN_SPCS_CODE:
             return "SE_DRM_TYP_SRM_SRFSM_WISCONSIN_SPCS_CODE";

        case SE_DRM_TYP_SRM_SRFT_CODE:
             return "SE_DRM_TYP_SRM_SRFT_CODE";

        case SE_DRM_TYP_SRM_SRFT_PARAMETERS:
             return "SE_DRM_TYP_SRM_SRFT_PARAMETERS";

        case SE_DRM_TYP_SE_STATE_MISMATCH_BEHAVIOUR:
             return "SE_DRM_TYP_SE_STATE_MISMATCH_BEHAVIOUR";

        case SE_DRM_TYP_EDCS_STATUS_CODE:
             return "SE_DRM_TYP_EDCS_STATUS_CODE";

        case SE_DRM_TYP_SRM_STATUS_CODE:
             return "SE_DRM_TYP_SRM_STATUS_CODE";

        case SE_DRM_TYP_EDCS_STRING:
             return "SE_DRM_TYP_EDCS_STRING";

        case SE_DRM_TYP_SE_STRING:
             return "SE_DRM_TYP_SE_STRING";

        case SE_DRM_TYP_SE_SYMBOL_FORMAT:
             return "SE_DRM_TYP_SE_SYMBOL_FORMAT";

        case SE_DRM_TYP_SE_TELEPHONE_INFORMATION:
             return "SE_DRM_TYP_SE_TELEPHONE_INFORMATION";

        case SE_DRM_TYP_SE_TEXT_FONT:
             return "SE_DRM_TYP_SE_TEXT_FONT";

        case SE_DRM_TYP_SE_TIME_CONFIGURATION:
             return "SE_DRM_TYP_SE_TIME_CONFIGURATION";

        case SE_DRM_TYP_SE_TIME_DATA_TYPE:
             return "SE_DRM_TYP_SE_TIME_DATA_TYPE";

        case SE_DRM_TYP_SE_TIME_DAY_OF_YEAR_VALUE:
             return "SE_DRM_TYP_SE_TIME_DAY_OF_YEAR_VALUE";

        case SE_DRM_TYP_SE_TIME_M_VALUE:
             return "SE_DRM_TYP_SE_TIME_M_VALUE";

        case SE_DRM_TYP_SE_TIME_MD_H_VALUE:
             return "SE_DRM_TYP_SE_TIME_MD_H_VALUE";

        case SE_DRM_TYP_SE_TIME_MD_HM_VALUE:
             return "SE_DRM_TYP_SE_TIME_MD_HM_VALUE";

        case SE_DRM_TYP_SE_TIME_MD_HMS_VALUE:
             return "SE_DRM_TYP_SE_TIME_MD_HMS_VALUE";

        case SE_DRM_TYP_SE_TIME_Y_VALUE:
             return "SE_DRM_TYP_SE_TIME_Y_VALUE";

        case SE_DRM_TYP_SE_TIME_YD_VALUE:
             return "SE_DRM_TYP_SE_TIME_YD_VALUE";

        case SE_DRM_TYP_SE_TIME_YD_H_VALUE:
             return "SE_DRM_TYP_SE_TIME_YD_H_VALUE";

        case SE_DRM_TYP_SE_TIME_YD_HM_VALUE:
             return "SE_DRM_TYP_SE_TIME_YD_HM_VALUE";

        case SE_DRM_TYP_SE_TIME_YD_HMS_VALUE:
             return "SE_DRM_TYP_SE_TIME_YD_HMS_VALUE";

        case SE_DRM_TYP_SE_TIME_YMD_VALUE:
             return "SE_DRM_TYP_SE_TIME_YMD_VALUE";

        case SE_DRM_TYP_SE_TIME_YMD_H_VALUE:
             return "SE_DRM_TYP_SE_TIME_YMD_H_VALUE";

        case SE_DRM_TYP_SE_TIME_YMD_HM_VALUE:
             return "SE_DRM_TYP_SE_TIME_YMD_HM_VALUE";

        case SE_DRM_TYP_SE_TIME_YMD_HMS_VALUE:
             return "SE_DRM_TYP_SE_TIME_YMD_HMS_VALUE";

        case SE_DRM_TYP_SE_TIME_OF_DAY:
             return "SE_DRM_TYP_SE_TIME_OF_DAY";

        case SE_DRM_TYP_SE_TIME_SIGNIFICANCE:
             return "SE_DRM_TYP_SE_TIME_SIGNIFICANCE";

        case SE_DRM_TYP_SE_TIME_VALUE:
             return "SE_DRM_TYP_SE_TIME_VALUE";

        case SE_DRM_TYP_SRM_TM_PARAMETERS:
             return "SE_DRM_TYP_SRM_TM_PARAMETERS";

        case SE_DRM_TYP_SE_TYPE_CLASSIFICATION:
             return "SE_DRM_TYP_SE_TYPE_CLASSIFICATION";

        case SE_DRM_TYP_SE_UNDERLINE_STYLE:
             return "SE_DRM_TYP_SE_UNDERLINE_STYLE";

        case SE_DRM_TYP_SE_UNION_REASON:
             return "SE_DRM_TYP_SE_UNION_REASON";

        case SE_DRM_TYP_EDCS_UNIT_CODE:
             return "SE_DRM_TYP_EDCS_UNIT_CODE";

        case SE_DRM_TYP_EDCS_UNIT_CONCEPT:
             return "SE_DRM_TYP_EDCS_UNIT_CONCEPT";

        case SE_DRM_TYP_EDCS_UNIT_DICTIONARY_ENTRY:
             return "SE_DRM_TYP_EDCS_UNIT_DICTIONARY_ENTRY";

        case SE_DRM_TYP_EDCS_UNIT_EQUIVALENCE_CODE:
             return "SE_DRM_TYP_EDCS_UNIT_EQUIVALENCE_CODE";

        case SE_DRM_TYP_EDCS_UNIT_EQUIVALENCE_DICTIONARY_ENTRY:
             return "SE_DRM_TYP_EDCS_UNIT_EQUIVALENCE_DICTIONARY_ENTRY";

        case SE_DRM_TYP_EDCS_UNIT_EQUIVALENCE_LABEL:
             return "SE_DRM_TYP_EDCS_UNIT_EQUIVALENCE_LABEL";

        case SE_DRM_TYP_EDCS_UNIT_LABEL:
             return "SE_DRM_TYP_EDCS_UNIT_LABEL";

        case SE_DRM_TYP_EDCS_UNIT_SCALE_CODE:
             return "SE_DRM_TYP_EDCS_UNIT_SCALE_CODE";

        case SE_DRM_TYP_EDCS_UNIT_SCALE_DICTIONARY_ENTRY:
             return "SE_DRM_TYP_EDCS_UNIT_SCALE_DICTIONARY_ENTRY";

        case SE_DRM_TYP_EDCS_UNIT_SCALE_LABEL:
             return "SE_DRM_TYP_EDCS_UNIT_SCALE_LABEL";

        case SE_DRM_TYP_EDCS_UNIT_STATUS:
             return "SE_DRM_TYP_EDCS_UNIT_STATUS";

        case SE_DRM_TYP_SRM_UNUSED:
             return "SE_DRM_TYP_SRM_UNUSED";

        case SE_DRM_TYP_SE_URL:
             return "SE_DRM_TYP_SE_URL";

        case SE_DRM_TYP_SE_URN:
             return "SE_DRM_TYP_SE_URN";

        case SE_DRM_TYP_EDCS_VALUE_CHARACTERISTIC_APPLICABILITY:
             return "SE_DRM_TYP_EDCS_VALUE_CHARACTERISTIC_APPLICABILITY";

        case SE_DRM_TYP_EDCS_VALUE_CHARACTERISTIC_CODE:
             return "SE_DRM_TYP_EDCS_VALUE_CHARACTERISTIC_CODE";

        case SE_DRM_TYP_EDCS_VALUE_CHARACTERISTIC_DICTIONARY_ENTRY:
             return "SE_DRM_TYP_EDCS_VALUE_CHARACTERISTIC_DICTIONARY_ENTRY";

        case SE_DRM_TYP_EDCS_VALUE_CHARACTERISTIC_LABEL:
             return "SE_DRM_TYP_EDCS_VALUE_CHARACTERISTIC_LABEL";

        case SE_DRM_TYP_SE_VARIABLE_CODE:
             return "SE_DRM_TYP_SE_VARIABLE_CODE";

        case SE_DRM_TYP_SRM_VECTOR_3D:
             return "SE_DRM_TYP_SRM_VECTOR_3D";

        case SE_DRM_TYP_SE_YIQ_DATA:
             return "SE_DRM_TYP_SE_YIQ_DATA";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_DRM_Type VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintDRMType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintElementType
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintElementType
(
    const SE_Element_Type *value_ptr,
    const char            *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Element_Type\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->code_type: %s\n", name_ptr,
                SE_PrintElementTypeCode(value_ptr->code_type));
        switch (value_ptr->code_type)
        {
            case SE_ELEMTYPCOD_ATTRIBUTE:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->code.attribute: %s\n", name_ptr,
                        EDCS_PrintAttributeCode(value_ptr->code.attribute));
                break;

            case SE_ELEMTYPCOD_INDEX:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->code.index: %s\n", name_ptr,
                        SE_PrintIndexCode(value_ptr->code.index));
                break;

            case SE_ELEMTYPCOD_VARIABLE:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->code.variable: %s\n", name_ptr,
                        SE_PrintVariableCode(value_ptr->code.variable));
                break;

        } /* end switch */
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "code_type: %s\n",
                SE_PrintElementTypeCode(value_ptr->code_type));
        switch (value_ptr->code_type)
        {
            case SE_ELEMTYPCOD_ATTRIBUTE:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "code.attribute: %s\n",
                        EDCS_PrintAttributeCode(value_ptr->code.attribute));
                break;

            case SE_ELEMTYPCOD_INDEX:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "code.index: %s\n",
                        SE_PrintIndexCode(value_ptr->code.index));
                break;

            case SE_ELEMTYPCOD_VARIABLE:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "code.variable: %s\n",
                        SE_PrintVariableCode(value_ptr->code.variable));
                break;

        } /* end switch */
    }
} /* end SE_PrintElementType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintElementTypeCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintElementTypeCode
(
    SE_Element_Type_Code value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_ELEMTYPCOD_ATTRIBUTE:
             return "SE_ELEMTYPCOD_ATTRIBUTE";

        case SE_ELEMTYPCOD_INDEX:
             return "SE_ELEMTYPCOD_INDEX";

        case SE_ELEMTYPCOD_VARIABLE:
             return "SE_ELEMTYPCOD_VARIABLE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Element_Type_Code VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintElementTypeCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintEnumerantStructure
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintEnumerantStructure
(
    const SE_Enumerant_Structure *value_ptr,
    const char                   *name_ptr,
          SE_Integer_Unsigned     level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Enumerant_Structure\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->abstract_name_ptr:", name_ptr);
        if (value_ptr->abstract_name_ptr != NULL)
        {
            fprintf(f_ptr, " %s", value_ptr->abstract_name_ptr);
        }
        fprintf(f_ptr, "\n");
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->name_ptr:", name_ptr);
        if (value_ptr->name_ptr != NULL)
        {
            fprintf(f_ptr, " %s", value_ptr->name_ptr);
        }
        fprintf(f_ptr, "\n");
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->value: %s\n", name_ptr, SE_PrintInteger
                (value_ptr->value));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "abstract_name_ptr:");
        if (value_ptr->abstract_name_ptr != NULL)
        {
            fprintf(f_ptr, " %s", value_ptr->abstract_name_ptr);
        }
        fprintf(f_ptr, "\n");
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "name_ptr:");
        if (value_ptr->name_ptr != NULL)
        {
            fprintf(f_ptr, " %s", value_ptr->name_ptr);
        }
        fprintf(f_ptr, "\n");
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "value: %s\n", SE_PrintInteger(value_ptr->value));
    }
} /* end SE_PrintEnumerantStructure */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintFeatureTopologyLevel
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintFeatureTopologyLevel
(
    SE_Feature_Topology_Level value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_FTL_ZERO:
             return "SE_FTL_ZERO";

        case SE_FTL_ONE:
             return "SE_FTL_ONE";

        case SE_FTL_TWO:
             return "SE_FTL_TWO";

        case SE_FTL_THREE:
             return "SE_FTL_THREE";

        case SE_FTL_FOUR:
             return "SE_FTL_FOUR";

        case SE_FTL_FIVE:
             return "SE_FTL_FIVE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Feature_Topology_Level VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintFeatureTopologyLevel */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintFieldModifier
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintFieldModifier
(
    SE_Field_Modifier value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_FLD_MDFR_PLAIN:
             return "SE_FLD_MDFR_PLAIN";

        case SE_FLD_MDFR_BIT:
             return "SE_FLD_MDFR_BIT";

        case SE_FLD_MDFR_1D_ARRAY:
             return "SE_FLD_MDFR_1D_ARRAY";

        case SE_FLD_MDFR_2D_ARRAY:
             return "SE_FLD_MDFR_2D_ARRAY";

        case SE_FLD_MDFR_POINTER:
             return "SE_FLD_MDFR_POINTER";

        case SE_FLD_MDFR_UNION:
             return "SE_FLD_MDFR_UNION";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Field_Modifier VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintFieldModifier */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintFloat
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintFloat
(
    SE_Float value
)
{
    static char buffer[100];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%*.*f",(int)SE_GetMinWidth(), (int)SE_GetPrecision(), (double)value);
    return buffer;
} /* end SE_PrintFloat */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintFontStyle
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintFontStyle
(
    SE_Font_Style value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_FONT_NORMAL:
             return "SE_FONT_NORMAL";

        case SE_FONT_BOLD:
             return "SE_FONT_BOLD";

        case SE_FONT_ITALIC:
             return "SE_FONT_ITALIC";

        case SE_FONT_BOLD_ITALIC:
             return "SE_FONT_BOLD_ITALIC";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Font_Style VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintFontStyle */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintFunctionalAssociationMeaningType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintFunctionalAssociationMeaningType
(
    SE_Functional_Association_Meaning_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_FNASSMNTYP_CONTROLS:
             return "SE_FNASSMNTYP_CONTROLS";

        case SE_FNASSMNTYP_CONTROLLED_BY:
             return "SE_FNASSMNTYP_CONTROLLED_BY";

        case SE_FNASSMNTYP_SUPPORTS:
             return "SE_FNASSMNTYP_SUPPORTS";

        case SE_FNASSMNTYP_SUPPORTED_BY:
             return "SE_FNASSMNTYP_SUPPORTED_BY";

        case SE_FNASSMNTYP_ATTACHED:
             return "SE_FNASSMNTYP_ATTACHED";

        default:
             sprintf(buffer,"ERROR - ILLEGAL"\
                    " SE_Functional_Association_Meaning_Type VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintFunctionalAssociationMeaningType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintGeometricCentreCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintGeometricCentreCode
(
    SE_Geometric_Centre_Code value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_GEOMCTRCOD_CENTRE_OF_BUOYANCY:
             return "SE_GEOMCTRCOD_CENTRE_OF_BUOYANCY";

        case SE_GEOMCTRCOD_CENTRE_OF_MASS:
             return "SE_GEOMCTRCOD_CENTRE_OF_MASS";

        case SE_GEOMCTRCOD_CENTRE_OF_PRESSURE:
             return "SE_GEOMCTRCOD_CENTRE_OF_PRESSURE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Geometric_Centre_Code VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintGeometricCentreCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintGeometryTopologyLevel
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintGeometryTopologyLevel
(
    SE_Geometry_Topology_Level value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_GTL_ZERO:
             return "SE_GTL_ZERO";

        case SE_GTL_ONE:
             return "SE_GTL_ONE";

        case SE_GTL_TWO:
             return "SE_GTL_TWO";

        case SE_GTL_THREE:
             return "SE_GTL_THREE";

        case SE_GTL_FOUR:
             return "SE_GTL_FOUR";

        case SE_GTL_FIVE:
             return "SE_GTL_FIVE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Geometry_Topology_Level"\
                    " VALUE (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintGeometryTopologyLevel */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintGridOverlapOperator
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintGridOverlapOperator
(
    SE_Grid_Overlap_Operator value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_GROVLOP_BASE:
             return "SE_GROVLOP_BASE";

        case SE_GROVLOP_REPLACE:
             return "SE_GROVLOP_REPLACE";

        case SE_GROVLOP_MERGE:
             return "SE_GROVLOP_MERGE";

        case SE_GROVLOP_ADD:
             return "SE_GROVLOP_ADD";

        case SE_GROVLOP_MEAN:
             return "SE_GROVLOP_MEAN";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Grid_Overlap_Operator VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintGridOverlapOperator */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintHLSData
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintHLSData
(
    const SE_HLS_Data *value_ptr,
    const char        *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_HLS_Data\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->hue: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->hue));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->lightness: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->lightness));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->saturation: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->saturation));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "hue: %s\n", SE_PrintLongFloat(value_ptr->hue));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "lightness: %s\n", SE_PrintLongFloat
                (value_ptr->lightness));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "saturation: %s\n", SE_PrintLongFloat
                (value_ptr->saturation));
    }
} /* end SE_PrintHLSData */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintHSMultiplicityCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintHSMultiplicityCode
(
    SE_HS_Multiplicity_Code value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_HSMULCOD_EXACT:
             return "SE_HSMULCOD_EXACT";

        case SE_HSMULCOD_ORDER_OF_MAGNITUDE:
             return "SE_HSMULCOD_ORDER_OF_MAGNITUDE";

        case SE_HSMULCOD_UNKNOWN:
             return "SE_HSMULCOD_UNKNOWN";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_HS_Multiplicity_Code VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintHSMultiplicityCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintHSVData
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintHSVData
(
    const SE_HSV_Data *value_ptr,
    const char        *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_HSV_Data\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->hue: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->hue));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->saturation: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->saturation));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->value: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->value));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "hue: %s\n", SE_PrintLongFloat(value_ptr->hue));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "saturation: %s\n", SE_PrintLongFloat
                (value_ptr->saturation));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "value: %s\n", SE_PrintLongFloat(value_ptr->value));
    }
} /* end SE_PrintHSVData */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintImageComponentType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintImageComponentType
(
    SE_Image_Component_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_IMAGCOMP_SIGNED_INTEGER:
             return "SE_IMAGCOMP_SIGNED_INTEGER";

        case SE_IMAGCOMP_UNSIGNED_INTEGER:
             return "SE_IMAGCOMP_UNSIGNED_INTEGER";

        case SE_IMAGCOMP_FLOATING_POINT:
             return "SE_IMAGCOMP_FLOATING_POINT";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Image_Component_Type VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintImageComponentType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintImageMappingMethod
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintImageMappingMethod
(
    SE_Image_Mapping_Method value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_IMAGMAPMETH_REPLACE:
             return "SE_IMAGMAPMETH_REPLACE";

        case SE_IMAGMAPMETH_DECAL:
             return "SE_IMAGMAPMETH_DECAL";

        case SE_IMAGMAPMETH_MODULATE:
             return "SE_IMAGMAPMETH_MODULATE";

        case SE_IMAGMAPMETH_BLEND:
             return "SE_IMAGMAPMETH_BLEND";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Image_Mapping_Method VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintImageMappingMethod */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintImageMIPExtents
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintImageMIPExtents
(
    const SE_Image_MIP_Extents *value_ptr,
    const char                 *name_ptr,
          SE_Integer_Unsigned   level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Image_MIP_Extents\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->size_horizontal: %s\n", name_ptr,
                SE_PrintIntegerPositive(value_ptr->size_horizontal));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->size_vertical: %s\n", name_ptr,
                SE_PrintIntegerPositive(value_ptr->size_vertical));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->size_z: %s\n", name_ptr, SE_PrintIntegerPositive
                (value_ptr->size_z));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "size_horizontal: %s\n", SE_PrintIntegerPositive
                (value_ptr->size_horizontal));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "size_vertical: %s\n", SE_PrintIntegerPositive
                (value_ptr->size_vertical));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "size_z: %s\n", SE_PrintIntegerPositive
                (value_ptr->size_z));
    }
} /* end SE_PrintImageMIPExtents */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintImageProjectionType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintImageProjectionType
(
    SE_Image_Projection_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_IMAGPROJTYP_PLANAR:
             return "SE_IMAGPROJTYP_PLANAR";

        case SE_IMAGPROJTYP_CYLINDRICAL:
             return "SE_IMAGPROJTYP_CYLINDRICAL";

        case SE_IMAGPROJTYP_SPHERICAL:
             return "SE_IMAGPROJTYP_SPHERICAL";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Image_Projection_Type VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintImageProjectionType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintImageScanDirection
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintImageScanDirection
(
    SE_Image_Scan_Direction value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_IMAGSCANDIR_RIGHT_UP:
             return "SE_IMAGSCANDIR_RIGHT_UP";

        case SE_IMAGSCANDIR_RIGHT_DOWN:
             return "SE_IMAGSCANDIR_RIGHT_DOWN";

        case SE_IMAGSCANDIR_DOWN_RIGHT:
             return "SE_IMAGSCANDIR_DOWN_RIGHT";

        case SE_IMAGSCANDIR_DOWN_LEFT:
             return "SE_IMAGSCANDIR_DOWN_LEFT";

        case SE_IMAGSCANDIR_LEFT_UP:
             return "SE_IMAGSCANDIR_LEFT_UP";

        case SE_IMAGSCANDIR_LEFT_DOWN:
             return "SE_IMAGSCANDIR_LEFT_DOWN";

        case SE_IMAGSCANDIR_UP_RIGHT:
             return "SE_IMAGSCANDIR_UP_RIGHT";

        case SE_IMAGSCANDIR_UP_LEFT:
             return "SE_IMAGSCANDIR_UP_LEFT";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Image_Scan_Direction VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintImageScanDirection */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintImageScanDirectionZ
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintImageScanDirectionZ
(
    SE_Image_Scan_Direction_Z value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_IMAGSCANDIRZ_NONE:
             return "SE_IMAGSCANDIRZ_NONE";

        case SE_IMAGSCANDIRZ_Z_BACK:
             return "SE_IMAGSCANDIRZ_Z_BACK";

        case SE_IMAGSCANDIRZ_Z_FRONT:
             return "SE_IMAGSCANDIRZ_Z_FRONT";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Image_Scan_Direction_Z VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintImageScanDirectionZ */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintImageSignature
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintImageSignature
(
    SE_Image_Signature value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_IMAGSIG_ALPHA:
             return "SE_IMAGSIG_ALPHA";

        case SE_IMAGSIG_LUMINANCE:
             return "SE_IMAGSIG_LUMINANCE";

        case SE_IMAGSIG_COLOUR_COORDINATE_1:
             return "SE_IMAGSIG_COLOUR_COORDINATE_1";

        case SE_IMAGSIG_COLOUR_COORDINATE_2:
             return "SE_IMAGSIG_COLOUR_COORDINATE_2";

        case SE_IMAGSIG_COLOUR_COORDINATE_3:
             return "SE_IMAGSIG_COLOUR_COORDINATE_3";

        case SE_IMAGSIG_BUMP_MAP_HEIGHT:
             return "SE_IMAGSIG_BUMP_MAP_HEIGHT";

        case SE_IMAGSIG_EDCS_CLASSIFICATION_CODE:
             return "SE_IMAGSIG_EDCS_CLASSIFICATION_CODE";

        case SE_IMAGSIG_LUMINANCE_AND_ALPHA:
             return "SE_IMAGSIG_LUMINANCE_AND_ALPHA";

        case SE_IMAGSIG_123COLOUR:
             return "SE_IMAGSIG_123COLOUR";

        case SE_IMAGSIG_123COLOUR_ALPHA:
             return "SE_IMAGSIG_123COLOUR_ALPHA";

        case SE_IMAGSIG_ONE_MATERIAL:
             return "SE_IMAGSIG_ONE_MATERIAL";

        case SE_IMAGSIG_TWO_MATERIALS:
             return "SE_IMAGSIG_TWO_MATERIALS";

        case SE_IMAGSIG_THREE_MATERIALS:
             return "SE_IMAGSIG_THREE_MATERIALS";

        case SE_IMAGSIG_IMAGE_INDEX:
             return "SE_IMAGSIG_IMAGE_INDEX";

        case SE_IMAGSIG_BUMP_MAP_UV:
             return "SE_IMAGSIG_BUMP_MAP_UV";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Image_Signature VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintImageSignature */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintImageWrap
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintImageWrap
(
    SE_Image_Wrap value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_IMAGWRAP_CLAMP:
             return "SE_IMAGWRAP_CLAMP";

        case SE_IMAGWRAP_REPEAT:
             return "SE_IMAGWRAP_REPEAT";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Image_Wrap VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintImageWrap */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintIndexCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintIndexCode
(
    SE_Index_Code value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_IDXCODE_DATA_TABLE_COMPONENT:
             return "SE_IDXCODE_DATA_TABLE_COMPONENT";

        case SE_IDXCODE_DATA_TABLE_LIBRARY:
             return "SE_IDXCODE_DATA_TABLE_LIBRARY";

        case SE_IDXCODE_IMAGE_MAPPING_FUNCTION:
             return "SE_IDXCODE_IMAGE_MAPPING_FUNCTION";

        case SE_IDXCODE_PROP_TABLE_REF_COMPONENT:
             return "SE_IDXCODE_PROP_TABLE_REF_COMPONENT";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Index_Code VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintIndexCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintInteger
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintInteger
(
    SE_Integer value
)
{
    static char buffer[100];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%i", (int) value);
    return buffer;
} /* end SE_PrintInteger */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintIntegerIntervalValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintIntegerIntervalValue
(
    const SE_Integer_Interval_Value *value_ptr,
    const char                      *name_ptr,
          SE_Integer_Unsigned        level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Integer_Interval_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->interval_type: %s\n", name_ptr,
                SE_PrintIntervalType(value_ptr->interval_type));
        switch (value_ptr->interval_type)
        {
            case SE_INTRVLTYP_OPEN_INTERVAL:
                sprintf(buffer, "%s->value.open_interval", name_ptr);
                EDCS_PrintIntegerInterval(&(value_ptr->value.open_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GE_LT_INTERVAL:
                sprintf(buffer, "%s->value.ge_lt_interval", name_ptr);
                EDCS_PrintIntegerInterval(&(value_ptr->value.ge_lt_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GT_LE_INTERVAL:
                sprintf(buffer, "%s->value.gt_le_interval", name_ptr);
                EDCS_PrintIntegerInterval(&(value_ptr->value.gt_le_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_CLOSED_INTERVAL:
                sprintf(buffer, "%s->value.closed_interval", name_ptr);
                EDCS_PrintIntegerInterval(&(value_ptr->value.closed_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.gt_semi_interval: %s\n", name_ptr,
                        EDCS_PrintInteger(value_ptr->value.gt_semi_interval));
                break;

            case SE_INTRVLTYP_GE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.ge_semi_interval: %s\n", name_ptr,
                        EDCS_PrintInteger(value_ptr->value.ge_semi_interval));
                break;

            case SE_INTRVLTYP_LT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.lt_semi_interval: %s\n", name_ptr,
                        EDCS_PrintInteger(value_ptr->value.lt_semi_interval));
                break;

            case SE_INTRVLTYP_LE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.le_semi_interval: %s\n", name_ptr,
                        EDCS_PrintInteger(value_ptr->value.le_semi_interval));
                break;

        } /* end switch */
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "interval_type: %s\n",
                SE_PrintIntervalType(value_ptr->interval_type));
        switch (value_ptr->interval_type)
        {
            case SE_INTRVLTYP_OPEN_INTERVAL:
                sprintf(buffer, "value.open_interval");
                EDCS_PrintIntegerInterval(&(value_ptr->value.open_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GE_LT_INTERVAL:
                sprintf(buffer, "value.ge_lt_interval");
                EDCS_PrintIntegerInterval(&(value_ptr->value.ge_lt_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GT_LE_INTERVAL:
                sprintf(buffer, "value.gt_le_interval");
                EDCS_PrintIntegerInterval(&(value_ptr->value.gt_le_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_CLOSED_INTERVAL:
                sprintf(buffer, "value.closed_interval");
                EDCS_PrintIntegerInterval(&(value_ptr->value.closed_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.gt_semi_interval: %s\n",
                        EDCS_PrintInteger(value_ptr->value.gt_semi_interval));
                break;

            case SE_INTRVLTYP_GE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.ge_semi_interval: %s\n",
                        EDCS_PrintInteger(value_ptr->value.ge_semi_interval));
                break;

            case SE_INTRVLTYP_LT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.lt_semi_interval: %s\n",
                        EDCS_PrintInteger(value_ptr->value.lt_semi_interval));
                break;

            case SE_INTRVLTYP_LE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.le_semi_interval: %s\n",
                        EDCS_PrintInteger(value_ptr->value.le_semi_interval));
                break;

        } /* end switch */
    }
} /* end SE_PrintIntegerIntervalValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintIntegerPositive
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintIntegerPositive
(
    SE_Integer_Positive value
)
{
    static char buffer[100];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%u", (unsigned int) value);
    return buffer;
} /* end SE_PrintIntegerPositive */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintIntegerUnsigned
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintIntegerUnsigned
(
    SE_Integer_Unsigned value
)
{
    static char buffer[100];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%u", (unsigned int) value);
    return buffer;
} /* end SE_PrintIntegerUnsigned */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintInterpolationType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintInterpolationType
(
    SE_Interpolation_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_INTERPTYP_BICUBIC_SPLINE:
             return "SE_INTERPTYP_BICUBIC_SPLINE";

        case SE_INTERPTYP_DIAGONALIZATION:
             return "SE_INTERPTYP_DIAGONALIZATION";

        case SE_INTERPTYP_DISALLOWED:
             return "SE_INTERPTYP_DISALLOWED";

        case SE_INTERPTYP_KRIGING:
             return "SE_INTERPTYP_KRIGING";

        case SE_INTERPTYP_LAGRANGIAN:
             return "SE_INTERPTYP_LAGRANGIAN";

        case SE_INTERPTYP_LINEAR:
             return "SE_INTERPTYP_LINEAR";

        case SE_INTERPTYP_METADATA_SPECIFIED:
             return "SE_INTERPTYP_METADATA_SPECIFIED";

        case SE_INTERPTYP_NEAREST_NEIGHBOUR:
             return "SE_INTERPTYP_NEAREST_NEIGHBOUR";

        case SE_INTERPTYP_NOT_SUPPLIED:
             return "SE_INTERPTYP_NOT_SUPPLIED";

        case SE_INTERPTYP_OAML_DBDB_SPLINE_FIT:
             return "SE_INTERPTYP_OAML_DBDB_SPLINE_FIT";

        case SE_INTERPTYP_QUADRATIC:
             return "SE_INTERPTYP_QUADRATIC";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Interpolation_Type VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintInterpolationType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintIntervalType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintIntervalType
(
    SE_Interval_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_INTRVLTYP_OPEN_INTERVAL:
             return "SE_INTRVLTYP_OPEN_INTERVAL";

        case SE_INTRVLTYP_GE_LT_INTERVAL:
             return "SE_INTRVLTYP_GE_LT_INTERVAL";

        case SE_INTRVLTYP_GT_LE_INTERVAL:
             return "SE_INTRVLTYP_GT_LE_INTERVAL";

        case SE_INTRVLTYP_CLOSED_INTERVAL:
             return "SE_INTRVLTYP_CLOSED_INTERVAL";

        case SE_INTRVLTYP_GT_SEMI_INTERVAL:
             return "SE_INTRVLTYP_GT_SEMI_INTERVAL";

        case SE_INTRVLTYP_GE_SEMI_INTERVAL:
             return "SE_INTRVLTYP_GE_SEMI_INTERVAL";

        case SE_INTRVLTYP_LT_SEMI_INTERVAL:
             return "SE_INTRVLTYP_LT_SEMI_INTERVAL";

        case SE_INTRVLTYP_LE_SEMI_INTERVAL:
             return "SE_INTRVLTYP_LE_SEMI_INTERVAL";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Interval_Type VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintIntervalType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintIntervalValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintIntervalValue
(
    const SE_Interval_Value *value_ptr,
    const char              *name_ptr,
          SE_Integer_Unsigned  level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Interval_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->value_type: %s\n", name_ptr,
                SE_PrintIntervalValueType(value_ptr->value_type));
        switch (value_ptr->value_type)
        {
            case SE_INTRVLVALTYP_FLOAT:
                sprintf(buffer, "%s->value.long_float_value", name_ptr);
                SE_PrintLongFloatIntervalValue(&(value_ptr->value.long_float_value),
                  buffer, level);
                break;

            case SE_INTRVLVALTYP_INTEGER:
                sprintf(buffer, "%s->value.integer_value", name_ptr);
                SE_PrintIntegerIntervalValue(&(value_ptr->value.integer_value),
                  buffer, level);
                break;

            case SE_INTRVLVALTYP_COUNT:
                sprintf(buffer, "%s->value.count_value", name_ptr);
                SE_PrintCountIntervalValue(&(value_ptr->value.count_value),
                  buffer, level);
                break;

        } /* end switch */
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "value_type: %s\n",
                SE_PrintIntervalValueType(value_ptr->value_type));
        switch (value_ptr->value_type)
        {
            case SE_INTRVLVALTYP_FLOAT:
                sprintf(buffer, "value.long_float_value");
                SE_PrintLongFloatIntervalValue(&(value_ptr->value.long_float_value),
                  buffer, level);
                break;

            case SE_INTRVLVALTYP_INTEGER:
                sprintf(buffer, "value.integer_value");
                SE_PrintIntegerIntervalValue(&(value_ptr->value.integer_value),
                  buffer, level);
                break;

            case SE_INTRVLVALTYP_COUNT:
                sprintf(buffer, "value.count_value");
                SE_PrintCountIntervalValue(&(value_ptr->value.count_value),
                  buffer, level);
                break;

        } /* end switch */
    }
} /* end SE_PrintIntervalValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintIntervalValueType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintIntervalValueType
(
    SE_Interval_Value_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_INTRVLVALTYP_FLOAT:
             return "SE_INTRVLVALTYP_FLOAT";

        case SE_INTRVLVALTYP_INTEGER:
             return "SE_INTRVLVALTYP_INTEGER";

        case SE_INTRVLVALTYP_COUNT:
             return "SE_INTRVLVALTYP_COUNT";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Interval_Value_Type VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintIntervalValueType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintLocale
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintLocale
(
    const SE_Locale *value_ptr,
    const char      *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;
    SE_Integer_Unsigned i;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Locale\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->language[0..1]: ", name_ptr);
        for (i = 0; i < 2; i++)
        {
            fprintf(f_ptr, "%c", value_ptr->language[i]);
        } /* end for i */
        fprintf(f_ptr, "\n");
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->country[0..2]: ", name_ptr);
        for (i = 0; i < 3; i++)
        {
            fprintf(f_ptr, "%c", value_ptr->country[i]);
        } /* end for i */
        fprintf(f_ptr, "\n");
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "language[0..1]: ");
        for (i = 0; i < 2; i++)
        {
            fprintf(f_ptr, "%c", value_ptr->language[i]);
        } /* end for i */
        fprintf(f_ptr, "\n");
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "country[0..2]: ");
        for (i = 0; i < 3; i++)
        {
            fprintf(f_ptr, "%c", value_ptr->country[i]);
        } /* end for i */
        fprintf(f_ptr, "\n");
    }
} /* end SE_PrintLocale */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintLODDataType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintLODDataType
(
    SE_LOD_Data_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_LODDATTYP_DISTANCE:
             return "SE_LODDATTYP_DISTANCE";

        case SE_LODDATTYP_INDEX:
             return "SE_LODDATTYP_INDEX";

        case SE_LODDATTYP_MAP_SCALE:
             return "SE_LODDATTYP_MAP_SCALE";

        case SE_LODDATTYP_VOLUME:
             return "SE_LODDATTYP_VOLUME";

        case SE_LODDATTYP_SPATIAL_RESOLUTION:
             return "SE_LODDATTYP_SPATIAL_RESOLUTION";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_LOD_Data_Type VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintLODDataType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintLongFloat
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintLongFloat
(
    SE_Long_Float value
)
{
    static char buffer[100];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%*.*f",(int)SE_GetMinWidth(), (int)SE_GetPrecision(), (double)value);
    return buffer;
} /* end SE_PrintLongFloat */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintLongFloatIntervalValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintLongFloatIntervalValue
(
    const SE_Long_Float_Interval_Value *value_ptr,
    const char                         *name_ptr,
          SE_Integer_Unsigned           level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Long_Float_Interval_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->interval_type: %s\n", name_ptr,
                SE_PrintIntervalType(value_ptr->interval_type));
        switch (value_ptr->interval_type)
        {
            case SE_INTRVLTYP_OPEN_INTERVAL:
                sprintf(buffer, "%s->value.open_interval", name_ptr);
                EDCS_PrintLongFloatInterval(&(value_ptr->value.open_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GE_LT_INTERVAL:
                sprintf(buffer, "%s->value.ge_lt_interval", name_ptr);
                EDCS_PrintLongFloatInterval(&(value_ptr->value.ge_lt_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GT_LE_INTERVAL:
                sprintf(buffer, "%s->value.gt_le_interval", name_ptr);
                EDCS_PrintLongFloatInterval(&(value_ptr->value.gt_le_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_CLOSED_INTERVAL:
                sprintf(buffer, "%s->value.closed_interval", name_ptr);
                EDCS_PrintLongFloatInterval(&(value_ptr->value.closed_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.gt_semi_interval: %s\n", name_ptr,
                        EDCS_PrintLongFloat
                        (value_ptr->value.gt_semi_interval));
                break;

            case SE_INTRVLTYP_GE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.ge_semi_interval: %s\n", name_ptr,
                        EDCS_PrintLongFloat
                        (value_ptr->value.ge_semi_interval));
                break;

            case SE_INTRVLTYP_LT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.lt_semi_interval: %s\n", name_ptr,
                        EDCS_PrintLongFloat
                        (value_ptr->value.lt_semi_interval));
                break;

            case SE_INTRVLTYP_LE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.le_semi_interval: %s\n", name_ptr,
                        EDCS_PrintLongFloat
                        (value_ptr->value.le_semi_interval));
                break;

        } /* end switch */
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "interval_type: %s\n",
                SE_PrintIntervalType(value_ptr->interval_type));
        switch (value_ptr->interval_type)
        {
            case SE_INTRVLTYP_OPEN_INTERVAL:
                sprintf(buffer, "value.open_interval");
                EDCS_PrintLongFloatInterval(&(value_ptr->value.open_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GE_LT_INTERVAL:
                sprintf(buffer, "value.ge_lt_interval");
                EDCS_PrintLongFloatInterval(&(value_ptr->value.ge_lt_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GT_LE_INTERVAL:
                sprintf(buffer, "value.gt_le_interval");
                EDCS_PrintLongFloatInterval(&(value_ptr->value.gt_le_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_CLOSED_INTERVAL:
                sprintf(buffer, "value.closed_interval");
                EDCS_PrintLongFloatInterval(&(value_ptr->value.closed_interval),
                  buffer, level);
                break;

            case SE_INTRVLTYP_GT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.gt_semi_interval: %s\n",
                        EDCS_PrintLongFloat
                        (value_ptr->value.gt_semi_interval));
                break;

            case SE_INTRVLTYP_GE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.ge_semi_interval: %s\n",
                        EDCS_PrintLongFloat
                        (value_ptr->value.ge_semi_interval));
                break;

            case SE_INTRVLTYP_LT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.lt_semi_interval: %s\n",
                        EDCS_PrintLongFloat
                        (value_ptr->value.lt_semi_interval));
                break;

            case SE_INTRVLTYP_LE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.le_semi_interval: %s\n",
                        EDCS_PrintLongFloat
                        (value_ptr->value.le_semi_interval));
                break;

        } /* end switch */
    }
} /* end SE_PrintLongFloatIntervalValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintLongFloatValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintLongFloatValue
(
    const SE_Long_Float_Value *value_ptr,
    const char                *name_ptr,
          SE_Integer_Unsigned  level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Long_Float_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->numeric_value_type: %s\n", name_ptr,
                EDCS_PrintNumericValueType(value_ptr->numeric_value_type));
        switch (value_ptr->numeric_value_type)
        {
            case EDCS_NVT_SINGLE_VALUE:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.single_value: %s\n", name_ptr,
                        EDCS_PrintLongFloat(value_ptr->value.single_value));
                break;

            case EDCS_NVT_OPEN_INTERVAL:
                sprintf(buffer, "%s->value.open_interval", name_ptr);
                EDCS_PrintLongFloatInterval(&(value_ptr->value.open_interval),
                  buffer, level);
                break;

            case EDCS_NVT_GE_LT_INTERVAL:
                sprintf(buffer, "%s->value.ge_lt_interval", name_ptr);
                EDCS_PrintLongFloatInterval(&(value_ptr->value.ge_lt_interval),
                  buffer, level);
                break;

            case EDCS_NVT_GT_LE_INTERVAL:
                sprintf(buffer, "%s->value.gt_le_interval", name_ptr);
                EDCS_PrintLongFloatInterval(&(value_ptr->value.gt_le_interval),
                  buffer, level);
                break;

            case EDCS_NVT_CLOSED_INTERVAL:
                sprintf(buffer, "%s->value.closed_interval", name_ptr);
                EDCS_PrintLongFloatInterval(&(value_ptr->value.closed_interval),
                  buffer, level);
                break;

            case EDCS_NVT_GT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.gt_semi_interval: %s\n", name_ptr,
                        EDCS_PrintLongFloat
                        (value_ptr->value.gt_semi_interval));
                break;

            case EDCS_NVT_GE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.ge_semi_interval: %s\n", name_ptr,
                        EDCS_PrintLongFloat
                        (value_ptr->value.ge_semi_interval));
                break;

            case EDCS_NVT_LT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.lt_semi_interval: %s\n", name_ptr,
                        EDCS_PrintLongFloat
                        (value_ptr->value.lt_semi_interval));
                break;

            case EDCS_NVT_LE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.le_semi_interval: %s\n", name_ptr,
                        EDCS_PrintLongFloat
                        (value_ptr->value.le_semi_interval));
                break;

        } /* end switch */
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "numeric_value_type: %s\n",
                EDCS_PrintNumericValueType(value_ptr->numeric_value_type));
        switch (value_ptr->numeric_value_type)
        {
            case EDCS_NVT_SINGLE_VALUE:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.single_value: %s\n", EDCS_PrintLongFloat
                        (value_ptr->value.single_value));
                break;

            case EDCS_NVT_OPEN_INTERVAL:
                sprintf(buffer, "value.open_interval");
                EDCS_PrintLongFloatInterval(&(value_ptr->value.open_interval),
                  buffer, level);
                break;

            case EDCS_NVT_GE_LT_INTERVAL:
                sprintf(buffer, "value.ge_lt_interval");
                EDCS_PrintLongFloatInterval(&(value_ptr->value.ge_lt_interval),
                  buffer, level);
                break;

            case EDCS_NVT_GT_LE_INTERVAL:
                sprintf(buffer, "value.gt_le_interval");
                EDCS_PrintLongFloatInterval(&(value_ptr->value.gt_le_interval),
                  buffer, level);
                break;

            case EDCS_NVT_CLOSED_INTERVAL:
                sprintf(buffer, "value.closed_interval");
                EDCS_PrintLongFloatInterval(&(value_ptr->value.closed_interval),
                  buffer, level);
                break;

            case EDCS_NVT_GT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.gt_semi_interval: %s\n",
                        EDCS_PrintLongFloat
                        (value_ptr->value.gt_semi_interval));
                break;

            case EDCS_NVT_GE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.ge_semi_interval: %s\n",
                        EDCS_PrintLongFloat
                        (value_ptr->value.ge_semi_interval));
                break;

            case EDCS_NVT_LT_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.lt_semi_interval: %s\n",
                        EDCS_PrintLongFloat
                        (value_ptr->value.lt_semi_interval));
                break;

            case EDCS_NVT_LE_SEMI_INTERVAL:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.le_semi_interval: %s\n",
                        EDCS_PrintLongFloat
                        (value_ptr->value.le_semi_interval));
                break;

        } /* end switch */
    }
} /* end SE_PrintLongFloatValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintLSRTransformationAxis
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintLSRTransformationAxis
(
    SE_LSR_Transformation_Axis value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_LSRAXIS_U:
             return "SE_LSRAXIS_U";

        case SE_LSRAXIS_V:
             return "SE_LSRAXIS_V";

        case SE_LSRAXIS_W:
             return "SE_LSRAXIS_W";

        case SE_LSRAXIS_ALL:
             return "SE_LSRAXIS_ALL";

        case SE_LSRAXIS_AXIS_REFERENCE_VECTOR:
             return "SE_LSRAXIS_AXIS_REFERENCE_VECTOR";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_LSR_Transformation_Axis"\
                    " VALUE (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintLSRTransformationAxis */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintMDClassificationCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintMDClassificationCode
(
    SE_MD_ClassificationCode value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_MD_CLSCOD_UNCLASSIFIED:
             return "SE_MD_CLSCOD_UNCLASSIFIED";

        case SE_MD_CLSCOD_RESTRICTED:
             return "SE_MD_CLSCOD_RESTRICTED";

        case SE_MD_CLSCOD_CONFIDENTIAL:
             return "SE_MD_CLSCOD_CONFIDENTIAL";

        case SE_MD_CLSCOD_SECRET:
             return "SE_MD_CLSCOD_SECRET";

        case SE_MD_CLSCOD_TOP_SECRET:
             return "SE_MD_CLSCOD_TOP_SECRET";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_MD_ClassificationCode VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintMDClassificationCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintMDKeywordTypeCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintMDKeywordTypeCode
(
    SE_MD_KeywordTypeCode value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_MD_KEYTYPCOD_DISCIPLINE:
             return "SE_MD_KEYTYPCOD_DISCIPLINE";

        case SE_MD_KEYTYPCOD_PLACE:
             return "SE_MD_KEYTYPCOD_PLACE";

        case SE_MD_KEYTYPCOD_STRATUM:
             return "SE_MD_KEYTYPCOD_STRATUM";

        case SE_MD_KEYTYPCOD_TEMPORAL:
             return "SE_MD_KEYTYPCOD_TEMPORAL";

        case SE_MD_KEYTYPCOD_THEME:
             return "SE_MD_KEYTYPCOD_THEME";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_MD_KeywordTypeCode VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintMDKeywordTypeCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintMDRestrictionCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintMDRestrictionCode
(
    SE_MD_RestrictionCode value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_MD_RESTRICTCOD_COPYRIGHT:
             return "SE_MD_RESTRICTCOD_COPYRIGHT";

        case SE_MD_RESTRICTCOD_PATENT:
             return "SE_MD_RESTRICTCOD_PATENT";

        case SE_MD_RESTRICTCOD_PATENT_PENDING:
             return "SE_MD_RESTRICTCOD_PATENT_PENDING";

        case SE_MD_RESTRICTCOD_TRADEMARK:
             return "SE_MD_RESTRICTCOD_TRADEMARK";

        case SE_MD_RESTRICTCOD_LICENSE:
             return "SE_MD_RESTRICTCOD_LICENSE";

        case SE_MD_RESTRICTCOD_INTELLECTUAL_PROPERTY_RIGHTS:
             return "SE_MD_RESTRICTCOD_INTELLECTUAL_PROPERTY_RIGHTS";

        case SE_MD_RESTRICTCOD_RESTRICTED:
             return "SE_MD_RESTRICTCOD_RESTRICTED";

        case SE_MD_RESTRICTCOD_OTHER_RESTRICTIONS:
             return "SE_MD_RESTRICTCOD_OTHER_RESTRICTIONS";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_MD_RestrictionCode VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintMDRestrictionCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintMediaFormat
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintMediaFormat
(
    SE_Media_Format value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_MEDIAFMT_AVI:
             return "SE_MEDIAFMT_AVI";

        case SE_MEDIAFMT_BIIF:
             return "SE_MEDIAFMT_BIIF";

        case SE_MEDIAFMT_BMP:
             return "SE_MEDIAFMT_BMP";

        case SE_MEDIAFMT_CGM:
             return "SE_MEDIAFMT_CGM";

        case SE_MEDIAFMT_GIF:
             return "SE_MEDIAFMT_GIF";

        case SE_MEDIAFMT_HTML:
             return "SE_MEDIAFMT_HTML";

        case SE_MEDIAFMT_JPEG:
             return "SE_MEDIAFMT_JPEG";

        case SE_MEDIAFMT_JPEG2000:
             return "SE_MEDIAFMT_JPEG2000";

        case SE_MEDIAFMT_NITFS:
             return "SE_MEDIAFMT_NITFS";

        case SE_MEDIAFMT_PICT:
             return "SE_MEDIAFMT_PICT";

        case SE_MEDIAFMT_PNG:
             return "SE_MEDIAFMT_PNG";

        case SE_MEDIAFMT_QT:
             return "SE_MEDIAFMT_QT";

        case SE_MEDIAFMT_RGB:
             return "SE_MEDIAFMT_RGB";

        case SE_MEDIAFMT_RIFF:
             return "SE_MEDIAFMT_RIFF";

        case SE_MEDIAFMT_SVG:
             return "SE_MEDIAFMT_SVG";

        case SE_MEDIAFMT_TIFF:
             return "SE_MEDIAFMT_TIFF";

        case SE_MEDIAFMT_WMF:
             return "SE_MEDIAFMT_WMF";

        case SE_MEDIAFMT_XBM:
             return "SE_MEDIAFMT_XBM";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Media_Format VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintMediaFormat */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintModelReferenceType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintModelReferenceType
(
    SE_Model_Reference_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_MODREFTYP_COMPONENT:
             return "SE_MODREFTYP_COMPONENT";

        case SE_MODREFTYP_ROOT:
             return "SE_MODREFTYP_ROOT";

        case SE_MODREFTYP_ROOT_AND_COMPONENT:
             return "SE_MODREFTYP_ROOT_AND_COMPONENT";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Model_Reference_Type VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintModelReferenceType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintMonth
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintMonth
(
    SE_Month value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_MONTH_JANUARY:
             return "SE_MONTH_JANUARY";

        case SE_MONTH_FEBRUARY:
             return "SE_MONTH_FEBRUARY";

        case SE_MONTH_MARCH:
             return "SE_MONTH_MARCH";

        case SE_MONTH_APRIL:
             return "SE_MONTH_APRIL";

        case SE_MONTH_MAY:
             return "SE_MONTH_MAY";

        case SE_MONTH_JUNE:
             return "SE_MONTH_JUNE";

        case SE_MONTH_JULY:
             return "SE_MONTH_JULY";

        case SE_MONTH_AUGUST:
             return "SE_MONTH_AUGUST";

        case SE_MONTH_SEPTEMBER:
             return "SE_MONTH_SEPTEMBER";

        case SE_MONTH_OCTOBER:
             return "SE_MONTH_OCTOBER";

        case SE_MONTH_NOVEMBER:
             return "SE_MONTH_NOVEMBER";

        case SE_MONTH_DECEMBER:
             return "SE_MONTH_DECEMBER";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Month VALUE (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintMonth */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintMultiplicity
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintMultiplicity
(
    SE_Multiplicity value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_MLTPCTY_EXACTLY_ONE:
             return "SE_MLTPCTY_EXACTLY_ONE";

        case SE_MLTPCTY_ZERO_OR_ONE:
             return "SE_MLTPCTY_ZERO_OR_ONE";

        case SE_MLTPCTY_ZERO_OR_MORE:
             return "SE_MLTPCTY_ZERO_OR_MORE";

        case SE_MLTPCTY_ONE_OR_MORE:
             return "SE_MLTPCTY_ONE_OR_MORE";

        case SE_MLTPCTY_EXACTLY_N:
             return "SE_MLTPCTY_EXACTLY_N";

        case SE_MLTPCTY_BOUNDED_ARRAY:
             return "SE_MLTPCTY_BOUNDED_ARRAY";

        case SE_MLTPCTY_UNBOUNDED_ARRAY:
             return "SE_MLTPCTY_UNBOUNDED_ARRAY";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Multiplicity VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintMultiplicity */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintOctant
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintOctant
(
    SE_Octant value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_OCTANT_UPPER_LEFT_FRONT:
             return "SE_OCTANT_UPPER_LEFT_FRONT";

        case SE_OCTANT_UPPER_LEFT_BACK:
             return "SE_OCTANT_UPPER_LEFT_BACK";

        case SE_OCTANT_LOWER_LEFT_FRONT:
             return "SE_OCTANT_LOWER_LEFT_FRONT";

        case SE_OCTANT_LOWER_LEFT_BACK:
             return "SE_OCTANT_LOWER_LEFT_BACK";

        case SE_OCTANT_UPPER_RIGHT_FRONT:
             return "SE_OCTANT_UPPER_RIGHT_FRONT";

        case SE_OCTANT_UPPER_RIGHT_BACK:
             return "SE_OCTANT_UPPER_RIGHT_BACK";

        case SE_OCTANT_LOWER_RIGHT_FRONT:
             return "SE_OCTANT_LOWER_RIGHT_FRONT";

        case SE_OCTANT_LOWER_RIGHT_BACK:
             return "SE_OCTANT_LOWER_RIGHT_BACK";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Octant VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintOctant */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintOctet
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintOctet
(
    SE_Octet value
)
{
    static char buffer[100];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%u", (unsigned int) value);
    return buffer;
} /* end SE_PrintOctet */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintOrderingReason
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintOrderingReason
(
    SE_Ordering_Reason value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_ORDREAS_NONE:
             return "SE_ORDREAS_NONE";

        case SE_ORDREAS_FIXED_LISTED:
             return "SE_ORDREAS_FIXED_LISTED";

        case SE_ORDREAS_LAYERED_FASTEST_RENDERING:
             return "SE_ORDREAS_LAYERED_FASTEST_RENDERING";

        case SE_ORDREAS_LAYERED_HIGH_QUALITY_RENDERING:
             return "SE_ORDREAS_LAYERED_HIGH_QUALITY_RENDERING";

        case SE_ORDREAS_SHARED_ATTRIBUTE:
             return "SE_ORDREAS_SHARED_ATTRIBUTE";

        case SE_ORDREAS_VIEWER_RANGE:
             return "SE_ORDREAS_VIEWER_RANGE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Ordering_Reason VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintOrderingReason */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintPixelFillMethod
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintPixelFillMethod
(
    SE_Pixel_Fill_Method value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_PIXFILLMETH_CONSTANT:
             return "SE_PIXFILLMETH_CONSTANT";

        case SE_PIXFILLMETH_BLEND:
             return "SE_PIXFILLMETH_BLEND";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Pixel_Fill_Method VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintPixelFillMethod */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintPointLightDisplayType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintPointLightDisplayType
(
    SE_Point_Light_Display_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_PTLTDISPTYP_RASTER:
             return "SE_PTLTDISPTYP_RASTER";

        case SE_PTLTDISPTYP_CALLIGRAPHIC:
             return "SE_PTLTDISPTYP_CALLIGRAPHIC";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Point_Light_Display_Type"\
                    " VALUE (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintPointLightDisplayType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintPolygonFlag
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintPolygonFlag
(
    const SE_Polygon_Flag *value_ptr,
    const char            *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Polygon_Flag\n");
        return;
    }
    if (name_ptr)
    {
    if (value_ptr->member.Backdrop_Ground)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Backdrop_Ground\n", name_ptr);
    }
    if (value_ptr->member.Backdrop_Sky)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Backdrop_Sky\n", name_ptr);
    }
    if (value_ptr->member.Clutter_Enhanced)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Clutter_Enhanced\n", name_ptr);
    }
    if (value_ptr->member.Collidible)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Collidible\n", name_ptr);
    }
    if (value_ptr->member.Concave)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Concave\n", name_ptr);
    }
    if (value_ptr->member.Cut)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Cut\n", name_ptr);
    }
    if (value_ptr->member.Cut_Imagery)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Cut_Imagery\n", name_ptr);
    }
    if (value_ptr->member.Decal)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Decal\n", name_ptr);
    }
    if (value_ptr->member.Dont_Drape)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Dont_Drape\n", name_ptr);
    }
    if (value_ptr->member.Enable_Feature_Size_Blending)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Enable_Feature_Size_Blending\n", name_ptr);
    }
    if (value_ptr->member.Enable_Fractal)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Enable_Fractal\n", name_ptr);
    }
    if (value_ptr->member.Enable_Polygon_Range_Blending)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Enable_Polygon_Range_Blending\n", name_ptr);
    }
    if (value_ptr->member.Footprint)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Footprint\n", name_ptr);
    }
    if (value_ptr->member.Hat_Test)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Hat_Test\n", name_ptr);
    }
    if (value_ptr->member.Inactive)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Inactive\n", name_ptr);
    }
    if (value_ptr->member.Invisible)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Invisible\n", name_ptr);
    }
    if (value_ptr->member.Laser_Range_Finding)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Laser_Range_Finding\n", name_ptr);
    }
    if (value_ptr->member.Moon_Reflection)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Moon_Reflection\n", name_ptr);
    }
    if (value_ptr->member.Opaque_Top)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Opaque_Top\n", name_ptr);
    }
    if (value_ptr->member.Projectile_Collidible)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Projectile_Collidible\n", name_ptr);
    }
    if (value_ptr->member.Raised)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Raised\n", name_ptr);
    }
    if (value_ptr->member.Reflective)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Reflective\n", name_ptr);
    }
    if (value_ptr->member.Shadow)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Shadow\n", name_ptr);
    }
    if (value_ptr->member.Sun_Illuminated)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Sun_Illuminated\n", name_ptr);
    }
    if (value_ptr->member.Terrain)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Terrain\n", name_ptr);
    }
    if (value_ptr->member.Visible_Floor)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Visible_Floor\n", name_ptr);
    }
    if (value_ptr->member.Visible_Interior)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Visible_Interior\n", name_ptr);
    }
    if (value_ptr->member.Visible_Perimeter)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Visible_Perimeter\n", name_ptr);
    }
    if (value_ptr->member.Waterbody_Surface)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Waterbody_Surface\n", name_ptr);
    }
    }
    else
    {
    if (value_ptr->member.Backdrop_Ground)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Backdrop_Ground\n");
    }
    if (value_ptr->member.Backdrop_Sky)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Backdrop_Sky\n");
    }
    if (value_ptr->member.Clutter_Enhanced)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Clutter_Enhanced\n");
    }
    if (value_ptr->member.Collidible)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Collidible\n");
    }
    if (value_ptr->member.Concave)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Concave\n");
    }
    if (value_ptr->member.Cut)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Cut\n");
    }
    if (value_ptr->member.Cut_Imagery)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Cut_Imagery\n");
    }
    if (value_ptr->member.Decal)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Decal\n");
    }
    if (value_ptr->member.Dont_Drape)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Dont_Drape\n");
    }
    if (value_ptr->member.Enable_Feature_Size_Blending)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Enable_Feature_Size_Blending\n");
    }
    if (value_ptr->member.Enable_Fractal)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Enable_Fractal\n");
    }
    if (value_ptr->member.Enable_Polygon_Range_Blending)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Enable_Polygon_Range_Blending\n");
    }
    if (value_ptr->member.Footprint)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Footprint\n");
    }
    if (value_ptr->member.Hat_Test)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Hat_Test\n");
    }
    if (value_ptr->member.Inactive)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Inactive\n");
    }
    if (value_ptr->member.Invisible)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Invisible\n");
    }
    if (value_ptr->member.Laser_Range_Finding)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Laser_Range_Finding\n");
    }
    if (value_ptr->member.Moon_Reflection)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Moon_Reflection\n");
    }
    if (value_ptr->member.Opaque_Top)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Opaque_Top\n");
    }
    if (value_ptr->member.Projectile_Collidible)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Projectile_Collidible\n");
    }
    if (value_ptr->member.Raised)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Raised\n");
    }
    if (value_ptr->member.Reflective)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Reflective\n");
    }
    if (value_ptr->member.Shadow)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Shadow\n");
    }
    if (value_ptr->member.Sun_Illuminated)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Sun_Illuminated\n");
    }
    if (value_ptr->member.Terrain)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Terrain\n");
    }
    if (value_ptr->member.Visible_Floor)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Visible_Floor\n");
    }
    if (value_ptr->member.Visible_Interior)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Visible_Interior\n");
    }
    if (value_ptr->member.Visible_Perimeter)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Visible_Perimeter\n");
    }
    if (value_ptr->member.Waterbody_Surface)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Waterbody_Surface\n");
    }
    }
} /* end SE_PrintPolygonFlag */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintPredefFuncArgStructure
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintPredefFuncArgStructure
(
    const SE_Predef_Func_Arg_Structure *value_ptr,
    const char                         *name_ptr,
          SE_Integer_Unsigned           level
)
{
    FILE *f_ptr;
    SE_Integer_Unsigned i;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Predef_Func_Arg_Structure\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->valid_type_count: %s\n", name_ptr,
                SE_PrintIntegerPositive(value_ptr->valid_type_count));
        if ((value_ptr->valid_type_count > 0) && (value_ptr->valid_type_array
            != NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned) value_ptr->valid_type_count;
                i++)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->valid_type_array[%u]: %s\n", name_ptr, i,
                        EDCS_PrintAttributeValueType
                        (value_ptr->valid_type_array[i]));
            } /* end for i */
        }
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "valid_type_count: %s\n", SE_PrintIntegerPositive
                (value_ptr->valid_type_count));
        if ((value_ptr->valid_type_count > 0) && (value_ptr->valid_type_array
            != NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned) value_ptr->valid_type_count;
                i++)
            {
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "valid_type_array[%u]: %s\n", i,
                        EDCS_PrintAttributeValueType
                        (value_ptr->valid_type_array[i]));
            } /* end for i */
        }
    }
} /* end SE_PrintPredefFuncArgStructure */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintPredefFuncStructure
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintPredefFuncStructure
(
    const SE_Predef_Func_Structure *value_ptr,
    const char                     *name_ptr,
          SE_Integer_Unsigned       level
)
{
    char  buffer[1024];
    FILE *f_ptr;
    SE_Integer_Unsigned i;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Predef_Func_Structure\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->argument_count: %s\n", name_ptr, SE_PrintInteger
                (value_ptr->argument_count));
        if ((value_ptr->argument_count > 0) && (value_ptr->argument_array !=
            NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned) value_ptr->argument_count;
                i++)
            {
                sprintf(buffer, "%s->argument_array[%u]", name_ptr, i);
                SE_PrintPredefFuncArgStructure(&(value_ptr->argument_array[i]),
                   buffer, level);
            } /* end for i */
        }
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "argument_count: %s\n", SE_PrintInteger
                (value_ptr->argument_count));
        if ((value_ptr->argument_count > 0) && (value_ptr->argument_array !=
            NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned) value_ptr->argument_count;
                i++)
            {
                sprintf(buffer, "argument_array[%u]", i);
                SE_PrintPredefFuncArgStructure(&(value_ptr->argument_array[i]),
                   buffer, level);
            } /* end for i */
        }
    }
} /* end SE_PrintPredefFuncStructure */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintPredefinedFunction
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintPredefinedFunction
(
    SE_Predefined_Function value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_PREDEFFN_ADD:
             return "SE_PREDEFFN_ADD";

        case SE_PREDEFFN_DIVIDE:
             return "SE_PREDEFFN_DIVIDE";

        case SE_PREDEFFN_MODULO:
             return "SE_PREDEFFN_MODULO";

        case SE_PREDEFFN_MULTIPLY:
             return "SE_PREDEFFN_MULTIPLY";

        case SE_PREDEFFN_SUBTRACT:
             return "SE_PREDEFFN_SUBTRACT";

        case SE_PREDEFFN_COSINE:
             return "SE_PREDEFFN_COSINE";

        case SE_PREDEFFN_SINE:
             return "SE_PREDEFFN_SINE";

        case SE_PREDEFFN_TANGENT:
             return "SE_PREDEFFN_TANGENT";

        case SE_PREDEFFN_ARCCOSINE:
             return "SE_PREDEFFN_ARCCOSINE";

        case SE_PREDEFFN_ARCSINE:
             return "SE_PREDEFFN_ARCSINE";

        case SE_PREDEFFN_ARCTANGENT:
             return "SE_PREDEFFN_ARCTANGENT";

        case SE_PREDEFFN_ARCTANGENT2:
             return "SE_PREDEFFN_ARCTANGENT2";

        case SE_PREDEFFN_HYPOTENUSE:
             return "SE_PREDEFFN_HYPOTENUSE";

        case SE_PREDEFFN_ABSOLUTE:
             return "SE_PREDEFFN_ABSOLUTE";

        case SE_PREDEFFN_EXPONENT:
             return "SE_PREDEFFN_EXPONENT";

        case SE_PREDEFFN_LN:
             return "SE_PREDEFFN_LN";

        case SE_PREDEFFN_LOG:
             return "SE_PREDEFFN_LOG";

        case SE_PREDEFFN_POWER:
             return "SE_PREDEFFN_POWER";

        case SE_PREDEFFN_SQRT:
             return "SE_PREDEFFN_SQRT";

        case SE_PREDEFFN_MAXIMUM:
             return "SE_PREDEFFN_MAXIMUM";

        case SE_PREDEFFN_MINIMUM:
             return "SE_PREDEFFN_MINIMUM";

        case SE_PREDEFFN_NOT:
             return "SE_PREDEFFN_NOT";

        case SE_PREDEFFN_AND:
             return "SE_PREDEFFN_AND";

        case SE_PREDEFFN_EQUAL:
             return "SE_PREDEFFN_EQUAL";

        case SE_PREDEFFN_GREATER_THAN:
             return "SE_PREDEFFN_GREATER_THAN";

        case SE_PREDEFFN_GREATER_THAN_OR_EQUAL:
             return "SE_PREDEFFN_GREATER_THAN_OR_EQUAL";

        case SE_PREDEFFN_LESS_THAN:
             return "SE_PREDEFFN_LESS_THAN";

        case SE_PREDEFFN_LESS_THAN_OR_EQUAL:
             return "SE_PREDEFFN_LESS_THAN_OR_EQUAL";

        case SE_PREDEFFN_NOT_EQUAL:
             return "SE_PREDEFFN_NOT_EQUAL";

        case SE_PREDEFFN_OR:
             return "SE_PREDEFFN_OR";

        case SE_PREDEFFN_EXCLUSIVE_OR:
             return "SE_PREDEFFN_EXCLUSIVE_OR";

        case SE_PREDEFFN_IF:
             return "SE_PREDEFFN_IF";

        case SE_PREDEFFN_PI:
             return "SE_PREDEFFN_PI";

        case SE_PREDEFFN_SIMULATION_TIME:
             return "SE_PREDEFFN_SIMULATION_TIME";

        case SE_PREDEFFN_SIMULATION_UTIME:
             return "SE_PREDEFFN_SIMULATION_UTIME";

        case SE_PREDEFFN_REFERENCE_SURFACE_ELEVATION:
             return "SE_PREDEFFN_REFERENCE_SURFACE_ELEVATION";

        case SE_PREDEFFN_CYCLE_TIME:
             return "SE_PREDEFFN_CYCLE_TIME";

        case SE_PREDEFFN_TABLE_VALUE:
             return "SE_PREDEFFN_TABLE_VALUE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Predefined_Function VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintPredefinedFunction */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintPresentIn
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintPresentIn
(
    SE_Present_In value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_PRESENT_IN_NONE:
             return "SE_PRESENT_IN_NONE";

        case SE_PRESENT_IN_ENVIRONMENT_ROOT:
             return "SE_PRESENT_IN_ENVIRONMENT_ROOT";

        case SE_PRESENT_IN_MODELS:
             return "SE_PRESENT_IN_MODELS";

        case SE_PRESENT_IN_ENVIRONMENT_ROOT_AND_MODELS:
             return "SE_PRESENT_IN_ENVIRONMENT_ROOT_AND_MODELS";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Present_In VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintPresentIn */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintPresentationDomain
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintPresentationDomain
(
    const SE_Presentation_Domain *value_ptr,
    const char                   *name_ptr,
          SE_Integer_Unsigned     level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Presentation_Domain\n");
        return;
    }
    if (name_ptr)
    {
    if (value_ptr->member.OTW)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.OTW\n", name_ptr);
    }
    if (value_ptr->member.IR_Hi_Band)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.IR_Hi_Band\n", name_ptr);
    }
    if (value_ptr->member.IR_Low_Band)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.IR_Low_Band\n", name_ptr);
    }
    if (value_ptr->member.NVG)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.NVG\n", name_ptr);
    }
    if (value_ptr->member.Day_TV_Colour)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Day_TV_Colour\n", name_ptr);
    }
    if (value_ptr->member.Day_TV_BW)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Day_TV_BW\n", name_ptr);
    }
    if (value_ptr->member.Radar)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Radar\n", name_ptr);
    }
    if (value_ptr->member.SAR)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.SAR\n", name_ptr);
    }
    if (value_ptr->member.Thermal)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Thermal\n", name_ptr);
    }
    if (value_ptr->member.Low_Light_TV)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->member.Low_Light_TV\n", name_ptr);
    }
    }
    else
    {
    if (value_ptr->member.OTW)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.OTW\n");
    }
    if (value_ptr->member.IR_Hi_Band)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.IR_Hi_Band\n");
    }
    if (value_ptr->member.IR_Low_Band)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.IR_Low_Band\n");
    }
    if (value_ptr->member.NVG)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.NVG\n");
    }
    if (value_ptr->member.Day_TV_Colour)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Day_TV_Colour\n");
    }
    if (value_ptr->member.Day_TV_BW)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Day_TV_BW\n");
    }
    if (value_ptr->member.Radar)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Radar\n");
    }
    if (value_ptr->member.SAR)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.SAR\n");
    }
    if (value_ptr->member.Thermal)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Thermal\n");
    }
    if (value_ptr->member.Low_Light_TV)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "member.Low_Light_TV\n");
    }
    }
} /* end SE_PrintPresentationDomain */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintPropertyCode
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintPropertyCode
(
    const SE_Property_Code *value_ptr,
    const char             *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Property_Code\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->code_type: %s\n", name_ptr,
                SE_PrintPropertyCodeType(value_ptr->code_type));
        switch (value_ptr->code_type)
        {
            case SE_PROPCODTYP_ATTRIBUTE:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->code.attribute: %s\n", name_ptr,
                        EDCS_PrintAttributeCode(value_ptr->code.attribute));
                break;

            case SE_PROPCODTYP_VARIABLE:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->code.variable: %s\n", name_ptr,
                        SE_PrintVariableCode(value_ptr->code.variable));
                break;

        } /* end switch */
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "code_type: %s\n",
                SE_PrintPropertyCodeType(value_ptr->code_type));
        switch (value_ptr->code_type)
        {
            case SE_PROPCODTYP_ATTRIBUTE:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "code.attribute: %s\n",
                        EDCS_PrintAttributeCode(value_ptr->code.attribute));
                break;

            case SE_PROPCODTYP_VARIABLE:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "code.variable: %s\n",
                        SE_PrintVariableCode(value_ptr->code.variable));
                break;

        } /* end switch */
    }
} /* end SE_PrintPropertyCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintPropertyCodeType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintPropertyCodeType
(
    SE_Property_Code_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_PROPCODTYP_ATTRIBUTE:
             return "SE_PROPCODTYP_ATTRIBUTE";

        case SE_PROPCODTYP_VARIABLE:
             return "SE_PROPCODTYP_VARIABLE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Property_Code_Type VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintPropertyCodeType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintQuadrant
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintQuadrant
(
    SE_Quadrant value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_QUADRANT_LEFT_FRONT:
             return "SE_QUADRANT_LEFT_FRONT";

        case SE_QUADRANT_RIGHT_FRONT:
             return "SE_QUADRANT_RIGHT_FRONT";

        case SE_QUADRANT_LEFT_BACK:
             return "SE_QUADRANT_LEFT_BACK";

        case SE_QUADRANT_RIGHT_BACK:
             return "SE_QUADRANT_RIGHT_BACK";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Quadrant VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintQuadrant */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintReferenceSurfaceElevationSelect
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintReferenceSurfaceElevationSelect
(
    SE_Reference_Surface_Elevation_Select value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_RSELEVSEL_CLOSEST_TO_ORM_CENTRE:
             return "SE_RSELEVSEL_CLOSEST_TO_ORM_CENTRE";

        case SE_RSELEVSEL_CLOSEST_TO_DSS:
             return "SE_RSELEVSEL_CLOSEST_TO_DSS";

        case SE_RSELEVSEL_FARTHEST_FROM_ORM_CENTRE:
             return "SE_RSELEVSEL_FARTHEST_FROM_ORM_CENTRE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL"\
                    " SE_Reference_Surface_Elevation_Select VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintReferenceSurfaceElevationSelect */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintReferenceSurfaceLODSelect
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintReferenceSurfaceLODSelect
(
    SE_Reference_Surface_LOD_Select value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_RSLODSEL_MOST_DETAILED:
             return "SE_RSLODSEL_MOST_DETAILED";

        case SE_RSLODSEL_LEAST_DETAILED:
             return "SE_RSLODSEL_LEAST_DETAILED";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Reference_Surface_LOD_Select"\
                    " VALUE (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintReferenceSurfaceLODSelect */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintReferenceVectorType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintReferenceVectorType
(
    SE_Reference_Vector_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_REFVEC_CAMERA_FORWARD_AXIS:
             return "SE_REFVEC_CAMERA_FORWARD_AXIS";

        case SE_REFVEC_CAMERA_UP_AXIS:
             return "SE_REFVEC_CAMERA_UP_AXIS";

        case SE_REFVEC_EMISSIVITY_AZIMUTH:
             return "SE_REFVEC_EMISSIVITY_AZIMUTH";

        case SE_REFVEC_EMISSIVITY_NORMAL:
             return "SE_REFVEC_EMISSIVITY_NORMAL";

        case SE_REFVEC_FACE_NORMAL:
             return "SE_REFVEC_FACE_NORMAL";

        case SE_REFVEC_LIGHT_DIRECTION:
             return "SE_REFVEC_LIGHT_DIRECTION";

        case SE_REFVEC_LSR_TRANSFORMATION_AXIS:
             return "SE_REFVEC_LSR_TRANSFORMATION_AXIS";

        case SE_REFVEC_MAJOR_AXIS:
             return "SE_REFVEC_MAJOR_AXIS";

        case SE_REFVEC_MINOR_AXIS:
             return "SE_REFVEC_MINOR_AXIS";

        case SE_REFVEC_MOVEMENT_DIRECTION:
             return "SE_REFVEC_MOVEMENT_DIRECTION";

        case SE_REFVEC_PARALLELEPIPED_EDGE_DIRECTION:
             return "SE_REFVEC_PARALLELEPIPED_EDGE_DIRECTION";

        case SE_REFVEC_REFLECTIVITY_AZIMUTH:
             return "SE_REFVEC_REFLECTIVITY_AZIMUTH";

        case SE_REFVEC_REFLECTIVITY_EMISSIVITY_AZIMUTH:
             return "SE_REFVEC_REFLECTIVITY_EMISSIVITY_AZIMUTH";

        case SE_REFVEC_REFLECTIVITY_EMISSIVITY_NORMAL:
             return "SE_REFVEC_REFLECTIVITY_EMISSIVITY_NORMAL";

        case SE_REFVEC_REFLECTIVITY_NORMAL:
             return "SE_REFVEC_REFLECTIVITY_NORMAL";

        case SE_REFVEC_RENDERING_NORMAL:
             return "SE_REFVEC_RENDERING_NORMAL";

        case SE_REFVEC_VERTICAL_AXIS:
             return "SE_REFVEC_VERTICAL_AXIS";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Reference_Vector_Type VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintReferenceVectorType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintRGBData
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintRGBData
(
    const SE_RGB_Data *value_ptr,
    const char        *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_RGB_Data\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->red: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->red));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->green: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->green));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->blue: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->blue));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "red: %s\n", SE_PrintLongFloat(value_ptr->red));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "green: %s\n", SE_PrintLongFloat(value_ptr->green));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "blue: %s\n", SE_PrintLongFloat(value_ptr->blue));
    }
} /* end SE_PrintRGBData */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintRotationData
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintRotationData
(
    const SE_Rotation_Data *value_ptr,
    const char             *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Rotation_Data\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->counterclockwise_limit: %s\n", name_ptr,
                SE_PrintLongFloat(value_ptr->counterclockwise_limit));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->clockwise_limit: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->clockwise_limit));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "counterclockwise_limit: %s\n", SE_PrintLongFloat
                (value_ptr->counterclockwise_limit));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "clockwise_limit: %s\n", SE_PrintLongFloat
                (value_ptr->clockwise_limit));
    }
} /* end SE_PrintRotationData */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintSeason
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintSeason
(
    SE_Season value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_SEASON_SPRING:
             return "SE_SEASON_SPRING";

        case SE_SEASON_SUMMER:
             return "SE_SEASON_SUMMER";

        case SE_SEASON_AUTUMN:
             return "SE_SEASON_AUTUMN";

        case SE_SEASON_WINTER:
             return "SE_SEASON_WINTER";

        case SE_SEASON_DRY:
             return "SE_SEASON_DRY";

        case SE_SEASON_WET:
             return "SE_SEASON_WET";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Season VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintSeason */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintShadingMethod
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintShadingMethod
(
    SE_Shading_Method value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_SHADMETH_NONE:
             return "SE_SHADMETH_NONE";

        case SE_SHADMETH_FLAT:
             return "SE_SHADMETH_FLAT";

        case SE_SHADMETH_INTERPOLATED_COLOUR:
             return "SE_SHADMETH_INTERPOLATED_COLOUR";

        case SE_SHADMETH_INTERPOLATED_NORMAL:
             return "SE_SHADMETH_INTERPOLATED_NORMAL";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Shading_Method VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintShadingMethod */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintShortInteger
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintShortInteger
(
    SE_Short_Integer value
)
{
    static char buffer[100];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%i", (int) value);
    return buffer;
} /* end SE_PrintShortInteger */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintShortIntegerPositive
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintShortIntegerPositive
(
    SE_Short_Integer_Positive value
)
{
    static char buffer[100];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%u", (unsigned int) value);
    return buffer;
} /* end SE_PrintShortIntegerPositive */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintShortIntegerUnsigned
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintShortIntegerUnsigned
(
    SE_Short_Integer_Unsigned value
)
{
    static char buffer[100];
               /*
                * for output string (or error message)
                */

    sprintf(buffer, "%u", (unsigned int) value);
    return buffer;
} /* end SE_PrintShortIntegerUnsigned */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintSingleValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintSingleValue
(
          EDCS_Attribute_Code     ea_code,
    const SE_Single_Value *value_ptr,
    const char            *name_ptr,
          SE_Integer_Unsigned  level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Single_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->value_type: %s\n", name_ptr,
                SE_PrintSingleValueType(value_ptr->value_type));
        switch (value_ptr->value_type)
        {
            case SE_SINGVALTYP_LONG_FLOAT:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.long_float_value: %s\n", name_ptr,
                        EDCS_PrintLongFloat
                        (value_ptr->value.long_float_value));
                break;

            case SE_SINGVALTYP_INTEGER:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.integer_value: %s\n", name_ptr,
                        EDCS_PrintInteger(value_ptr->value.integer_value));
                break;

            case SE_SINGVALTYP_COUNT:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.count_value: %s\n", name_ptr,
                        EDCS_PrintCount(value_ptr->value.count_value));
                break;

            case SE_SINGVALTYP_INDEX:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.index_value: %s\n", name_ptr,
                        EDCS_PrintInteger(value_ptr->value.index_value));
                break;

            case SE_SINGVALTYP_STRING:
                sprintf(buffer, "%s->value.string_value", name_ptr);
                EDCS_PrintString(&(value_ptr->value.string_value), buffer,
                  level);
                break;

            case SE_SINGVALTYP_CONSTRAINED_STRING:
                sprintf(buffer, "%s->value.constrained_string_value", name_ptr);
                EDCS_PrintString(&(value_ptr->value.constrained_string_value),
                  buffer, level);
                break;

            case SE_SINGVALTYP_KEY:
                sprintf(buffer, "%s->value.key_value", name_ptr);
                EDCS_PrintString(&(value_ptr->value.key_value), buffer, level);
                break;

            case SE_SINGVALTYP_ENUMERATION:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.enumerant_value: %s\n", name_ptr,
                        EDCS_PrintEnumerantCode(ea_code,
                        value_ptr->value.enumerant_value));
                break;

            case SE_SINGVALTYP_BOOLEAN:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "%s->value.boolean_value: %s\n", name_ptr,
                        EDCS_PrintBoolean(value_ptr->value.boolean_value));
                break;

        } /* end switch */
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "value_type: %s\n",
                SE_PrintSingleValueType(value_ptr->value_type));
        switch (value_ptr->value_type)
        {
            case SE_SINGVALTYP_LONG_FLOAT:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.long_float_value: %s\n",
                        EDCS_PrintLongFloat
                        (value_ptr->value.long_float_value));
                break;

            case SE_SINGVALTYP_INTEGER:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.integer_value: %s\n", EDCS_PrintInteger
                        (value_ptr->value.integer_value));
                break;

            case SE_SINGVALTYP_COUNT:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.count_value: %s\n", EDCS_PrintCount
                        (value_ptr->value.count_value));
                break;

            case SE_SINGVALTYP_INDEX:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.index_value: %s\n", EDCS_PrintInteger
                        (value_ptr->value.index_value));
                break;

            case SE_SINGVALTYP_STRING:
                sprintf(buffer, "value.string_value");
                EDCS_PrintString(&(value_ptr->value.string_value), buffer,
                  level);
                break;

            case SE_SINGVALTYP_CONSTRAINED_STRING:
                sprintf(buffer, "value.constrained_string_value");
                EDCS_PrintString(&(value_ptr->value.constrained_string_value),
                  buffer, level);
                break;

            case SE_SINGVALTYP_KEY:
                sprintf(buffer, "value.key_value");
                EDCS_PrintString(&(value_ptr->value.key_value), buffer, level);
                break;

            case SE_SINGVALTYP_ENUMERATION:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.enumerant_value: %s\n",
                        EDCS_PrintEnumerantCode(ea_code,
                        value_ptr->value.enumerant_value));
                break;

            case SE_SINGVALTYP_BOOLEAN:
                SE_Indent(level, f_ptr);
                fprintf(f_ptr, "value.boolean_value: %s\n",
                        EDCS_PrintBoolean(value_ptr->value.boolean_value));
                break;

        } /* end switch */
    }
} /* end SE_PrintSingleValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintSingleValueType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintSingleValueType
(
    SE_Single_Value_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_SINGVALTYP_LONG_FLOAT:
             return "SE_SINGVALTYP_LONG_FLOAT";

        case SE_SINGVALTYP_INTEGER:
             return "SE_SINGVALTYP_INTEGER";

        case SE_SINGVALTYP_COUNT:
             return "SE_SINGVALTYP_COUNT";

        case SE_SINGVALTYP_INDEX:
             return "SE_SINGVALTYP_INDEX";

        case SE_SINGVALTYP_STRING:
             return "SE_SINGVALTYP_STRING";

        case SE_SINGVALTYP_CONSTRAINED_STRING:
             return "SE_SINGVALTYP_CONSTRAINED_STRING";

        case SE_SINGVALTYP_KEY:
             return "SE_SINGVALTYP_KEY";

        case SE_SINGVALTYP_ENUMERATION:
             return "SE_SINGVALTYP_ENUMERATION";

        case SE_SINGVALTYP_BOOLEAN:
             return "SE_SINGVALTYP_BOOLEAN";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Single_Value_Type VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintSingleValueType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintSoundFormat
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintSoundFormat
(
    SE_Sound_Format value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_SOUNDFMT_AIFC:
             return "SE_SOUNDFMT_AIFC";

        case SE_SOUNDFMT_AIFF:
             return "SE_SOUNDFMT_AIFF";

        case SE_SOUNDFMT_AVI:
             return "SE_SOUNDFMT_AVI";

        case SE_SOUNDFMT_IFF:
             return "SE_SOUNDFMT_IFF";

        case SE_SOUNDFMT_MIDI:
             return "SE_SOUNDFMT_MIDI";

        case SE_SOUNDFMT_MP2:
             return "SE_SOUNDFMT_MP2";

        case SE_SOUNDFMT_MP3:
             return "SE_SOUNDFMT_MP3";

        case SE_SOUNDFMT_MPG:
             return "SE_SOUNDFMT_MPG";

        case SE_SOUNDFMT_QT:
             return "SE_SOUNDFMT_QT";

        case SE_SOUNDFMT_RA:
             return "SE_SOUNDFMT_RA";

        case SE_SOUNDFMT_SND:
             return "SE_SOUNDFMT_SND";

        case SE_SOUNDFMT_VOC:
             return "SE_SOUNDFMT_VOC";

        case SE_SOUNDFMT_WAV:
             return "SE_SOUNDFMT_WAV";

        case SE_SOUNDFMT_WVE:
             return "SE_SOUNDFMT_WVE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Sound_Format VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintSoundFormat */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintSpacingType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintSpacingType
(
    SE_Spacing_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_SPACTYP_ARITHMETIC:
             return "SE_SPACTYP_ARITHMETIC";

        case SE_SPACTYP_GEOMETRIC:
             return "SE_SPACTYP_GEOMETRIC";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Spacing_Type VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintSpacingType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintSpatialAssociationMeaningType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintSpatialAssociationMeaningType
(
    SE_Spatial_Association_Meaning_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_SPATASSMEANTYP_ALTERNATE_REPRESENTATION:
             return "SE_SPATASSMEANTYP_ALTERNATE_REPRESENTATION";

        case SE_SPATASSMEANTYP_CONTAINS:
             return "SE_SPATASSMEANTYP_CONTAINS";

        case SE_SPATASSMEANTYP_CONTAINED_BY:
             return "SE_SPATASSMEANTYP_CONTAINED_BY";

        case SE_SPATASSMEANTYP_CROSS:
             return "SE_SPATASSMEANTYP_CROSS";

        case SE_SPATASSMEANTYP_DISJOINT:
             return "SE_SPATASSMEANTYP_DISJOINT";

        case SE_SPATASSMEANTYP_INTERSECTS:
             return "SE_SPATASSMEANTYP_INTERSECTS";

        case SE_SPATASSMEANTYP_OVERLAP:
             return "SE_SPATASSMEANTYP_OVERLAP";

        case SE_SPATASSMEANTYP_TOUCH:
             return "SE_SPATASSMEANTYP_TOUCH";

        case SE_SPATASSMEANTYP_IN_PROXIMITY_OF:
             return "SE_SPATASSMEANTYP_IN_PROXIMITY_OF";

        case SE_SPATASSMEANTYP_COMPLETELY_ABOVE:
             return "SE_SPATASSMEANTYP_COMPLETELY_ABOVE";

        case SE_SPATASSMEANTYP_PARTIALLY_ABOVE:
             return "SE_SPATASSMEANTYP_PARTIALLY_ABOVE";

        case SE_SPATASSMEANTYP_COMPLETELY_BELOW:
             return "SE_SPATASSMEANTYP_COMPLETELY_BELOW";

        case SE_SPATASSMEANTYP_PARTIALLY_BELOW:
             return "SE_SPATASSMEANTYP_PARTIALLY_BELOW";

        default:
             sprintf(buffer,"ERROR - ILLEGAL"\
                    " SE_Spatial_Association_Meaning_Type VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintSpatialAssociationMeaningType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintSpatialIndexSpacingUnit
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintSpatialIndexSpacingUnit
(
    SE_Spatial_Index_Spacing_Unit value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_SISPACUNITS_METRE:
             return "SE_SISPACUNITS_METRE";

        case SE_SISPACUNITS_ARC_SECOND:
             return "SE_SISPACUNITS_ARC_SECOND";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Spatial_Index_Spacing_Unit"\
                    " VALUE (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintSpatialIndexSpacingUnit */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintSRFContextInfo
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintSRFContextInfo
(
    const SE_SRF_Context_Info *value_ptr,
    const char                *name_ptr,
          SE_Integer_Unsigned  level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_SRF_Context_Info\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->angular_unit: %s\n", name_ptr,
                EDCS_PrintUnitCode(value_ptr->angular_unit));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->linear_unit: %s\n", name_ptr,
                EDCS_PrintUnitCode(value_ptr->linear_unit));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->linear_scale: %s\n", name_ptr,
                EDCS_PrintUnitScaleCode(value_ptr->linear_scale));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->use_dss_code: %s\n", name_ptr,
                SE_PrintBoolean(value_ptr->use_dss_code));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->dss_code: %s\n", name_ptr,
                SRM_PrintDSSCode(value_ptr->dss_code));
        sprintf(buffer, "%s->srf_parameters_info", name_ptr);
        SRM_PrintSRFParametersInfo(&(value_ptr->srf_parameters_info), buffer,
          level);
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "angular_unit: %s\n",
                EDCS_PrintUnitCode(value_ptr->angular_unit));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "linear_unit: %s\n",
                EDCS_PrintUnitCode(value_ptr->linear_unit));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "linear_scale: %s\n",
                EDCS_PrintUnitScaleCode(value_ptr->linear_scale));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "use_dss_code: %s\n",
                SE_PrintBoolean(value_ptr->use_dss_code));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "dss_code: %s\n",
                SRM_PrintDSSCode(value_ptr->dss_code));
        sprintf(buffer, "srf_parameters_info");
        SRM_PrintSRFParametersInfo(&(value_ptr->srf_parameters_info), buffer,
          level);
    }
} /* end SE_PrintSRFContextInfo */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintStateMismatchBehaviour
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintStateMismatchBehaviour
(
    SE_State_Mismatch_Behaviour value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_STMISMBEH_DEFAULT:
             return "SE_STMISMBEH_DEFAULT";

        case SE_STMISMBEH_LAST:
             return "SE_STMISMBEH_LAST";

        case SE_STMISMBEH_NONE:
             return "SE_STMISMBEH_NONE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_State_Mismatch_Behaviour"\
                    " VALUE (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintStateMismatchBehaviour */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintString
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintString
(
    const SE_String *value_ptr,
    const char      *name_ptr,
          SE_Integer_Unsigned  level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_String\n");
        return;
    }
    if (name_ptr)
    {
        sprintf(buffer, "%s->locale", name_ptr);
        SE_PrintLocale(&(value_ptr->locale), buffer, level);
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->length: %s\n", name_ptr, SE_PrintIntegerUnsigned
                (value_ptr->length));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->characters:", name_ptr);
        if (value_ptr->characters != NULL)
        {
            fprintf(f_ptr, " %s", value_ptr->characters);
        }
        fprintf(f_ptr, "\n");
    }
    else
    {
        sprintf(buffer, "locale");
        SE_PrintLocale(&(value_ptr->locale), buffer, level);
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "length: %s\n", SE_PrintIntegerUnsigned
                (value_ptr->length));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "characters:");
        if (value_ptr->characters != NULL)
        {
            fprintf(f_ptr, " %s", value_ptr->characters);
        }
        fprintf(f_ptr, "\n");
    }
} /* end SE_PrintString */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintSymbolFormat
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintSymbolFormat
(
    SE_Symbol_Format value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_SYMBFMT_CGM:
             return "SE_SYMBFMT_CGM";

        case SE_SYMBFMT_SVG:
             return "SE_SYMBFMT_SVG";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Symbol_Format VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintSymbolFormat */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTelephoneInformation
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTelephoneInformation
(
    const SE_Telephone_Information *value_ptr,
    const char                     *name_ptr,
          SE_Integer_Unsigned       level
)
{
    char  buffer[1024];
    FILE *f_ptr;
    SE_Integer_Unsigned i;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Telephone_Information\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->voice_count: %s\n", name_ptr,
                SE_PrintShortIntegerUnsigned(value_ptr->voice_count));
        if ((value_ptr->voice_count > 0) && (value_ptr->voice != NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned) value_ptr->voice_count; i++)
            {
                sprintf(buffer, "%s->voice[%u]", name_ptr, i);
                SE_PrintString(&(value_ptr->voice[i]), buffer, level);
            } /* end for i */
        }
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->facsimile_count: %s\n", name_ptr,
                SE_PrintShortIntegerUnsigned(value_ptr->facsimile_count));
        if ((value_ptr->facsimile_count > 0) && (value_ptr->facsimile != NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned) value_ptr->facsimile_count;
                i++)
            {
                sprintf(buffer, "%s->facsimile[%u]", name_ptr, i);
                SE_PrintString(&(value_ptr->facsimile[i]), buffer, level);
            } /* end for i */
        }
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->tdd_tty_count: %s\n", name_ptr,
                SE_PrintShortIntegerUnsigned(value_ptr->tdd_tty_count));
        if ((value_ptr->tdd_tty_count > 0) && (value_ptr->tdd_tty != NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned) value_ptr->tdd_tty_count;
                i++)
            {
                sprintf(buffer, "%s->tdd_tty[%u]", name_ptr, i);
                SE_PrintString(&(value_ptr->tdd_tty[i]), buffer, level);
            } /* end for i */
        }
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "voice_count: %s\n", SE_PrintShortIntegerUnsigned
                (value_ptr->voice_count));
        if ((value_ptr->voice_count > 0) && (value_ptr->voice != NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned) value_ptr->voice_count; i++)
            {
                sprintf(buffer, "voice[%u]", i);
                SE_PrintString(&(value_ptr->voice[i]), buffer, level);
            } /* end for i */
        }
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "facsimile_count: %s\n", SE_PrintShortIntegerUnsigned
                (value_ptr->facsimile_count));
        if ((value_ptr->facsimile_count > 0) && (value_ptr->facsimile != NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned) value_ptr->facsimile_count;
                i++)
            {
                sprintf(buffer, "facsimile[%u]", i);
                SE_PrintString(&(value_ptr->facsimile[i]), buffer, level);
            } /* end for i */
        }
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "tdd_tty_count: %s\n", SE_PrintShortIntegerUnsigned
                (value_ptr->tdd_tty_count));
        if ((value_ptr->tdd_tty_count > 0) && (value_ptr->tdd_tty != NULL))
        {
            for (i = 0; i < (SE_Integer_Unsigned) value_ptr->tdd_tty_count;
                i++)
            {
                sprintf(buffer, "tdd_tty[%u]", i);
                SE_PrintString(&(value_ptr->tdd_tty[i]), buffer, level);
            } /* end for i */
        }
    }
} /* end SE_PrintTelephoneInformation */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTextFont
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTextFont
(
    const SE_Text_Font *value_ptr,
    const char         *name_ptr,
          SE_Integer_Unsigned  level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Text_Font\n");
        return;
    }
    if (name_ptr)
    {
        sprintf(buffer, "%s->font_family", name_ptr);
        SE_PrintString(&(value_ptr->font_family), buffer, level);
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->font_style: %s\n", name_ptr,
                SE_PrintFontStyle(value_ptr->font_style));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->font_size: %s\n", name_ptr, SE_PrintFloat
                (value_ptr->font_size));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->underline_style: %s\n", name_ptr,
                SE_PrintUnderlineStyle(value_ptr->underline_style));
    }
    else
    {
        sprintf(buffer, "font_family");
        SE_PrintString(&(value_ptr->font_family), buffer, level);
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "font_style: %s\n",
                SE_PrintFontStyle(value_ptr->font_style));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "font_size: %s\n", SE_PrintFloat(value_ptr->font_size));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "underline_style: %s\n",
                SE_PrintUnderlineStyle(value_ptr->underline_style));
    }
} /* end SE_PrintTextFont */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeConfiguration
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintTimeConfiguration
(
    SE_Time_Configuration value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_TIMECFG_DATE_YMD_AND_TIME_HMS:
             return "SE_TIMECFG_DATE_YMD_AND_TIME_HMS";

        case SE_TIMECFG_DATE_YMD_AND_TIME_HM:
             return "SE_TIMECFG_DATE_YMD_AND_TIME_HM";

        case SE_TIMECFG_DATE_YMD_AND_TIME_H:
             return "SE_TIMECFG_DATE_YMD_AND_TIME_H";

        case SE_TIMECFG_DATE_YMD:
             return "SE_TIMECFG_DATE_YMD";

        case SE_TIMECFG_DATE_YD_AND_TIME_HMS:
             return "SE_TIMECFG_DATE_YD_AND_TIME_HMS";

        case SE_TIMECFG_DATE_YD_AND_TIME_HM:
             return "SE_TIMECFG_DATE_YD_AND_TIME_HM";

        case SE_TIMECFG_DATE_YD_AND_TIME_H:
             return "SE_TIMECFG_DATE_YD_AND_TIME_H";

        case SE_TIMECFG_DATE_YD:
             return "SE_TIMECFG_DATE_YD";

        case SE_TIMECFG_DATE_MD_AND_TIME_HMS:
             return "SE_TIMECFG_DATE_MD_AND_TIME_HMS";

        case SE_TIMECFG_DATE_MD_AND_TIME_HM:
             return "SE_TIMECFG_DATE_MD_AND_TIME_HM";

        case SE_TIMECFG_DATE_MD_AND_TIME_H:
             return "SE_TIMECFG_DATE_MD_AND_TIME_H";

        case SE_TIMECFG_DATE_Y:
             return "SE_TIMECFG_DATE_Y";

        case SE_TIMECFG_DATE_M:
             return "SE_TIMECFG_DATE_M";

        case SE_TIMECFG_DAY_OF_YEAR:
             return "SE_TIMECFG_DAY_OF_YEAR";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Time_Configuration VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintTimeConfiguration */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeDataType
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintTimeDataType
(
    SE_Time_Data_Type value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_TIMEDATTYP_SEASON:
             return "SE_TIMEDATTYP_SEASON";

        case SE_TIMEDATTYP_TIME_INTERVAL:
             return "SE_TIMEDATTYP_TIME_INTERVAL";

        case SE_TIMEDATTYP_TIME_OF_DAY:
             return "SE_TIMEDATTYP_TIME_OF_DAY";

        case SE_TIMEDATTYP_TIME_POINT:
             return "SE_TIMEDATTYP_TIME_POINT";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Time_Data_Type VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintTimeDataType */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeDayOfYearValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeDayOfYearValue
(
    const SE_Time_Day_Of_Year_Value *value_ptr,
    const char                      *name_ptr,
          SE_Integer_Unsigned        level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_Day_Of_Year_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->day_of_year: %s\n", name_ptr,
                SE_PrintShortIntegerPositive(value_ptr->day_of_year));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "day_of_year: %s\n", SE_PrintShortIntegerPositive
                (value_ptr->day_of_year));
    }
} /* end SE_PrintTimeDayOfYearValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeMValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeMValue
(
    const SE_Time_M_Value *value_ptr,
    const char            *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_M_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->month: %s\n", name_ptr,
                SE_PrintMonth(value_ptr->month));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "month: %s\n", SE_PrintMonth(value_ptr->month));
    }
} /* end SE_PrintTimeMValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeMDHValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeMDHValue
(
    const SE_Time_MD_H_Value *value_ptr,
    const char               *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_MD_H_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->month: %s\n", name_ptr,
                SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->day: %s\n", name_ptr, SE_PrintShortIntegerPositive
                (value_ptr->day));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->hour: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->hour));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "month: %s\n", SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "day: %s\n", SE_PrintShortIntegerPositive
                (value_ptr->day));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "hour: %s\n", SE_PrintByteUnsigned(value_ptr->hour));
    }
} /* end SE_PrintTimeMDHValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeMDHMValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeMDHMValue
(
    const SE_Time_MD_HM_Value *value_ptr,
    const char                *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_MD_HM_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->month: %s\n", name_ptr,
                SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->day: %s\n", name_ptr, SE_PrintShortIntegerPositive
                (value_ptr->day));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->hour: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->hour));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->minutes: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->minutes));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "month: %s\n", SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "day: %s\n", SE_PrintShortIntegerPositive
                (value_ptr->day));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "hour: %s\n", SE_PrintByteUnsigned(value_ptr->hour));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "minutes: %s\n", SE_PrintByteUnsigned
                (value_ptr->minutes));
    }
} /* end SE_PrintTimeMDHMValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeMDHMSValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeMDHMSValue
(
    const SE_Time_MD_HMS_Value *value_ptr,
    const char                 *name_ptr,
          SE_Integer_Unsigned   level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_MD_HMS_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->month: %s\n", name_ptr,
                SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->day: %s\n", name_ptr, SE_PrintShortIntegerPositive
                (value_ptr->day));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->hour: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->hour));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->minutes: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->minutes));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->seconds: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->seconds));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "month: %s\n", SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "day: %s\n", SE_PrintShortIntegerPositive
                (value_ptr->day));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "hour: %s\n", SE_PrintByteUnsigned(value_ptr->hour));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "minutes: %s\n", SE_PrintByteUnsigned
                (value_ptr->minutes));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "seconds: %s\n", SE_PrintLongFloat(value_ptr->seconds));
    }
} /* end SE_PrintTimeMDHMSValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeOfDay
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintTimeOfDay
(
    SE_Time_Of_Day value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_TIMEOFDAY_DAWN:
             return "SE_TIMEOFDAY_DAWN";

        case SE_TIMEOFDAY_MORNING:
             return "SE_TIMEOFDAY_MORNING";

        case SE_TIMEOFDAY_DAY:
             return "SE_TIMEOFDAY_DAY";

        case SE_TIMEOFDAY_AFTERNOON:
             return "SE_TIMEOFDAY_AFTERNOON";

        case SE_TIMEOFDAY_DUSK:
             return "SE_TIMEOFDAY_DUSK";

        case SE_TIMEOFDAY_EVENING:
             return "SE_TIMEOFDAY_EVENING";

        case SE_TIMEOFDAY_NIGHT:
             return "SE_TIMEOFDAY_NIGHT";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Time_Of_Day VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintTimeOfDay */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeSignificance
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintTimeSignificance
(
    SE_Time_Significance value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_TIMESIGNIF_ANALYSIS:
             return "SE_TIMESIGNIF_ANALYSIS";

        case SE_TIMESIGNIF_CERTIFICATION_DATE:
             return "SE_TIMESIGNIF_CERTIFICATION_DATE";

        case SE_TIMESIGNIF_CREATION_DATE:
             return "SE_TIMESIGNIF_CREATION_DATE";

        case SE_TIMESIGNIF_FORECAST:
             return "SE_TIMESIGNIF_FORECAST";

        case SE_TIMESIGNIF_MODIFICATION_DATE:
             return "SE_TIMESIGNIF_MODIFICATION_DATE";

        case SE_TIMESIGNIF_OBSERVATION:
             return "SE_TIMESIGNIF_OBSERVATION";

        case SE_TIMESIGNIF_OCCURRENCE:
             return "SE_TIMESIGNIF_OCCURRENCE";

        case SE_TIMESIGNIF_PERIOD_OF_CONTENT:
             return "SE_TIMESIGNIF_PERIOD_OF_CONTENT";

        case SE_TIMESIGNIF_PUBLICATION_DATE:
             return "SE_TIMESIGNIF_PUBLICATION_DATE";

        case SE_TIMESIGNIF_REFERENCE:
             return "SE_TIMESIGNIF_REFERENCE";

        case SE_TIMESIGNIF_REVISION_DATE:
             return "SE_TIMESIGNIF_REVISION_DATE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Time_Significance VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintTimeSignificance */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeValue
(
    const SE_Time_Value *value_ptr,
    const char          *name_ptr,
          SE_Integer_Unsigned  level
)
{
    char  buffer[1024];
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->configuration: %s\n", name_ptr,
                SE_PrintTimeConfiguration(value_ptr->configuration));
        switch (value_ptr->configuration)
        {
            case SE_TIMECFG_DATE_YMD_AND_TIME_HMS:
                sprintf(buffer, "%s->value.ymd_hms", name_ptr);
                SE_PrintTimeYMDHMSValue(&(value_ptr->value.ymd_hms), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_YMD_AND_TIME_HM:
                sprintf(buffer, "%s->value.ymd_hm", name_ptr);
                SE_PrintTimeYMDHMValue(&(value_ptr->value.ymd_hm), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_YMD_AND_TIME_H:
                sprintf(buffer, "%s->value.ymd_h", name_ptr);
                SE_PrintTimeYMDHValue(&(value_ptr->value.ymd_h), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_YMD:
                sprintf(buffer, "%s->value.ymd", name_ptr);
                SE_PrintTimeYMDValue(&(value_ptr->value.ymd), buffer, level);
                break;

            case SE_TIMECFG_DATE_YD_AND_TIME_HMS:
                sprintf(buffer, "%s->value.yd_hms", name_ptr);
                SE_PrintTimeYDHMSValue(&(value_ptr->value.yd_hms), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_YD_AND_TIME_HM:
                sprintf(buffer, "%s->value.yd_hm", name_ptr);
                SE_PrintTimeYDHMValue(&(value_ptr->value.yd_hm), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_YD_AND_TIME_H:
                sprintf(buffer, "%s->value.yd_h", name_ptr);
                SE_PrintTimeYDHValue(&(value_ptr->value.yd_h), buffer, level);
                break;

            case SE_TIMECFG_DATE_YD:
                sprintf(buffer, "%s->value.yd", name_ptr);
                SE_PrintTimeYDValue(&(value_ptr->value.yd), buffer, level);
                break;

            case SE_TIMECFG_DATE_MD_AND_TIME_HMS:
                sprintf(buffer, "%s->value.md_hms", name_ptr);
                SE_PrintTimeMDHMSValue(&(value_ptr->value.md_hms), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_MD_AND_TIME_HM:
                sprintf(buffer, "%s->value.md_hm", name_ptr);
                SE_PrintTimeMDHMValue(&(value_ptr->value.md_hm), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_MD_AND_TIME_H:
                sprintf(buffer, "%s->value.md_h", name_ptr);
                SE_PrintTimeMDHValue(&(value_ptr->value.md_h), buffer, level);
                break;

            case SE_TIMECFG_DATE_Y:
                sprintf(buffer, "%s->value.year", name_ptr);
                SE_PrintTimeYValue(&(value_ptr->value.year), buffer, level);
                break;

            case SE_TIMECFG_DATE_M:
                sprintf(buffer, "%s->value.month", name_ptr);
                SE_PrintTimeMValue(&(value_ptr->value.month), buffer, level);
                break;

            case SE_TIMECFG_DAY_OF_YEAR:
                sprintf(buffer, "%s->value.day_of_year", name_ptr);
                SE_PrintTimeDayOfYearValue(&(value_ptr->value.day_of_year),
                  buffer, level);
                break;

        } /* end switch */
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "configuration: %s\n",
                SE_PrintTimeConfiguration(value_ptr->configuration));
        switch (value_ptr->configuration)
        {
            case SE_TIMECFG_DATE_YMD_AND_TIME_HMS:
                sprintf(buffer, "value.ymd_hms");
                SE_PrintTimeYMDHMSValue(&(value_ptr->value.ymd_hms), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_YMD_AND_TIME_HM:
                sprintf(buffer, "value.ymd_hm");
                SE_PrintTimeYMDHMValue(&(value_ptr->value.ymd_hm), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_YMD_AND_TIME_H:
                sprintf(buffer, "value.ymd_h");
                SE_PrintTimeYMDHValue(&(value_ptr->value.ymd_h), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_YMD:
                sprintf(buffer, "value.ymd");
                SE_PrintTimeYMDValue(&(value_ptr->value.ymd), buffer, level);
                break;

            case SE_TIMECFG_DATE_YD_AND_TIME_HMS:
                sprintf(buffer, "value.yd_hms");
                SE_PrintTimeYDHMSValue(&(value_ptr->value.yd_hms), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_YD_AND_TIME_HM:
                sprintf(buffer, "value.yd_hm");
                SE_PrintTimeYDHMValue(&(value_ptr->value.yd_hm), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_YD_AND_TIME_H:
                sprintf(buffer, "value.yd_h");
                SE_PrintTimeYDHValue(&(value_ptr->value.yd_h), buffer, level);
                break;

            case SE_TIMECFG_DATE_YD:
                sprintf(buffer, "value.yd");
                SE_PrintTimeYDValue(&(value_ptr->value.yd), buffer, level);
                break;

            case SE_TIMECFG_DATE_MD_AND_TIME_HMS:
                sprintf(buffer, "value.md_hms");
                SE_PrintTimeMDHMSValue(&(value_ptr->value.md_hms), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_MD_AND_TIME_HM:
                sprintf(buffer, "value.md_hm");
                SE_PrintTimeMDHMValue(&(value_ptr->value.md_hm), buffer,
                  level);
                break;

            case SE_TIMECFG_DATE_MD_AND_TIME_H:
                sprintf(buffer, "value.md_h");
                SE_PrintTimeMDHValue(&(value_ptr->value.md_h), buffer, level);
                break;

            case SE_TIMECFG_DATE_Y:
                sprintf(buffer, "value.year");
                SE_PrintTimeYValue(&(value_ptr->value.year), buffer, level);
                break;

            case SE_TIMECFG_DATE_M:
                sprintf(buffer, "value.month");
                SE_PrintTimeMValue(&(value_ptr->value.month), buffer, level);
                break;

            case SE_TIMECFG_DAY_OF_YEAR:
                sprintf(buffer, "value.day_of_year");
                SE_PrintTimeDayOfYearValue(&(value_ptr->value.day_of_year),
                  buffer, level);
                break;

        } /* end switch */
    }
} /* end SE_PrintTimeValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeYValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeYValue
(
    const SE_Time_Y_Value *value_ptr,
    const char            *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_Y_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->year: %s\n", name_ptr, SE_PrintInteger
                (value_ptr->year));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "year: %s\n", SE_PrintInteger(value_ptr->year));
    }
} /* end SE_PrintTimeYValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeYDHValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeYDHValue
(
    const SE_Time_YD_H_Value *value_ptr,
    const char               *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_YD_H_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->year: %s\n", name_ptr, SE_PrintInteger
                (value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->day_of_year: %s\n", name_ptr,
                SE_PrintShortIntegerPositive(value_ptr->day_of_year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->hour: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->hour));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "year: %s\n", SE_PrintInteger(value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "day_of_year: %s\n", SE_PrintShortIntegerPositive
                (value_ptr->day_of_year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "hour: %s\n", SE_PrintByteUnsigned(value_ptr->hour));
    }
} /* end SE_PrintTimeYDHValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeYDHMValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeYDHMValue
(
    const SE_Time_YD_HM_Value *value_ptr,
    const char                *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_YD_HM_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->year: %s\n", name_ptr, SE_PrintInteger
                (value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->day_of_year: %s\n", name_ptr,
                SE_PrintShortIntegerPositive(value_ptr->day_of_year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->hour: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->hour));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->minutes: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->minutes));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "year: %s\n", SE_PrintInteger(value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "day_of_year: %s\n", SE_PrintShortIntegerPositive
                (value_ptr->day_of_year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "hour: %s\n", SE_PrintByteUnsigned(value_ptr->hour));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "minutes: %s\n", SE_PrintByteUnsigned
                (value_ptr->minutes));
    }
} /* end SE_PrintTimeYDHMValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeYDHMSValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeYDHMSValue
(
    const SE_Time_YD_HMS_Value *value_ptr,
    const char                 *name_ptr,
          SE_Integer_Unsigned   level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_YD_HMS_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->year: %s\n", name_ptr, SE_PrintInteger
                (value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->day_of_year: %s\n", name_ptr,
                SE_PrintShortIntegerPositive(value_ptr->day_of_year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->hour: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->hour));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->minutes: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->minutes));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->seconds: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->seconds));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "year: %s\n", SE_PrintInteger(value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "day_of_year: %s\n", SE_PrintShortIntegerPositive
                (value_ptr->day_of_year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "hour: %s\n", SE_PrintByteUnsigned(value_ptr->hour));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "minutes: %s\n", SE_PrintByteUnsigned
                (value_ptr->minutes));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "seconds: %s\n", SE_PrintLongFloat(value_ptr->seconds));
    }
} /* end SE_PrintTimeYDHMSValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeYDValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeYDValue
(
    const SE_Time_YD_Value *value_ptr,
    const char             *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_YD_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->year: %s\n", name_ptr, SE_PrintInteger
                (value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->day_of_year: %s\n", name_ptr,
                SE_PrintShortIntegerPositive(value_ptr->day_of_year));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "year: %s\n", SE_PrintInteger(value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "day_of_year: %s\n", SE_PrintShortIntegerPositive
                (value_ptr->day_of_year));
    }
} /* end SE_PrintTimeYDValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeYMDHValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeYMDHValue
(
    const SE_Time_YMD_H_Value *value_ptr,
    const char                *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_YMD_H_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->year: %s\n", name_ptr, SE_PrintInteger
                (value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->month: %s\n", name_ptr,
                SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->day: %s\n", name_ptr, SE_PrintBytePositive
                (value_ptr->day));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->hour: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->hour));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "year: %s\n", SE_PrintInteger(value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "month: %s\n", SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "day: %s\n", SE_PrintBytePositive(value_ptr->day));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "hour: %s\n", SE_PrintByteUnsigned(value_ptr->hour));
    }
} /* end SE_PrintTimeYMDHValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeYMDHMValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeYMDHMValue
(
    const SE_Time_YMD_HM_Value *value_ptr,
    const char                 *name_ptr,
          SE_Integer_Unsigned   level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_YMD_HM_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->year: %s\n", name_ptr, SE_PrintInteger
                (value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->month: %s\n", name_ptr,
                SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->day: %s\n", name_ptr, SE_PrintBytePositive
                (value_ptr->day));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->hour: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->hour));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->minutes: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->minutes));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "year: %s\n", SE_PrintInteger(value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "month: %s\n", SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "day: %s\n", SE_PrintBytePositive(value_ptr->day));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "hour: %s\n", SE_PrintByteUnsigned(value_ptr->hour));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "minutes: %s\n", SE_PrintByteUnsigned
                (value_ptr->minutes));
    }
} /* end SE_PrintTimeYMDHMValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeYMDHMSValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeYMDHMSValue
(
    const SE_Time_YMD_HMS_Value *value_ptr,
    const char                  *name_ptr,
          SE_Integer_Unsigned    level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_YMD_HMS_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->year: %s\n", name_ptr, SE_PrintInteger
                (value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->month: %s\n", name_ptr,
                SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->day: %s\n", name_ptr, SE_PrintBytePositive
                (value_ptr->day));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->hour: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->hour));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->minutes: %s\n", name_ptr, SE_PrintByteUnsigned
                (value_ptr->minutes));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->seconds: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->seconds));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "year: %s\n", SE_PrintInteger(value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "month: %s\n", SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "day: %s\n", SE_PrintBytePositive(value_ptr->day));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "hour: %s\n", SE_PrintByteUnsigned(value_ptr->hour));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "minutes: %s\n", SE_PrintByteUnsigned
                (value_ptr->minutes));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "seconds: %s\n", SE_PrintLongFloat(value_ptr->seconds));
    }
} /* end SE_PrintTimeYMDHMSValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTimeYMDValue
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintTimeYMDValue
(
    const SE_Time_YMD_Value *value_ptr,
    const char              *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_Time_YMD_Value\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->year: %s\n", name_ptr, SE_PrintInteger
                (value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->month: %s\n", name_ptr,
                SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->day: %s\n", name_ptr, SE_PrintBytePositive
                (value_ptr->day));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "year: %s\n", SE_PrintInteger(value_ptr->year));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "month: %s\n", SE_PrintMonth(value_ptr->month));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "day: %s\n", SE_PrintBytePositive(value_ptr->day));
    }
} /* end SE_PrintTimeYMDValue */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintTypeClassification
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintTypeClassification
(
    SE_Type_Classification value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_TYP_CLASSIF_BASIC:
             return "SE_TYP_CLASSIF_BASIC";

        case SE_TYP_CLASSIF_ENUM:
             return "SE_TYP_CLASSIF_ENUM";

        case SE_TYP_CLASSIF_REGISTERABLE_ENUM:
             return "SE_TYP_CLASSIF_REGISTERABLE_ENUM";

        case SE_TYP_CLASSIF_SET:
             return "SE_TYP_CLASSIF_SET";

        case SE_TYP_CLASSIF_STRUCT:
             return "SE_TYP_CLASSIF_STRUCT";

        case SE_TYP_CLASSIF_FUNCTION:
             return "SE_TYP_CLASSIF_FUNCTION";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Type_Classification VALUE"\
                    " (%i)",(int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintTypeClassification */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintUnderlineStyle
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintUnderlineStyle
(
    SE_Underline_Style value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_ULSTYL_NONE:
             return "SE_ULSTYL_NONE";

        case SE_ULSTYL_SINGLE:
             return "SE_ULSTYL_SINGLE";

        case SE_ULSTYL_DOUBLE:
             return "SE_ULSTYL_DOUBLE";

        case SE_ULSTYL_BOLD_SINGLE:
             return "SE_ULSTYL_BOLD_SINGLE";

        case SE_ULSTYL_BOLD_DOUBLE:
             return "SE_ULSTYL_BOLD_DOUBLE";

        case SE_ULSTYL_DASHED:
             return "SE_ULSTYL_DASHED";

        case SE_ULSTYL_DOTTED:
             return "SE_ULSTYL_DOTTED";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Underline_Style VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintUnderlineStyle */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintUnionReason
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintUnionReason
(
    SE_Union_Reason value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_UNIONREAS_CLASSIFIED_OBJECT:
             return "SE_UNIONREAS_CLASSIFIED_OBJECT";

        case SE_UNIONREAS_COLLECTION_OF_CLASSIFIED_OBJECTS:
             return "SE_UNIONREAS_COLLECTION_OF_CLASSIFIED_OBJECTS";

        case SE_UNIONREAS_OTHER:
             return "SE_UNIONREAS_OTHER";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Union_Reason VALUE (%i)",(int)
                    value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintUnionReason */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintURL
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintURL
(
    const SE_URL *value_ptr,
    const char   *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_URL\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->length: %s\n", name_ptr, SE_PrintIntegerUnsigned
                (value_ptr->length));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->characters:", name_ptr);
        if (value_ptr->characters != NULL)
        {
            fprintf(f_ptr, " %s", value_ptr->characters);
        }
        fprintf(f_ptr, "\n");
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "length: %s\n", SE_PrintIntegerUnsigned
                (value_ptr->length));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "characters:");
        if (value_ptr->characters != NULL)
        {
            fprintf(f_ptr, " %s", value_ptr->characters);
        }
        fprintf(f_ptr, "\n");
    }
} /* end SE_PrintURL */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintURN
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintURN
(
    const SE_URN *value_ptr,
    const char   *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_URN\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->length: %s\n", name_ptr, SE_PrintIntegerUnsigned
                (value_ptr->length));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->characters:", name_ptr);
        if (value_ptr->characters != NULL)
        {
            fprintf(f_ptr, " %s", value_ptr->characters);
        }
        fprintf(f_ptr, "\n");
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "length: %s\n", SE_PrintIntegerUnsigned
                (value_ptr->length));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "characters:");
        if (value_ptr->characters != NULL)
        {
            fprintf(f_ptr, " %s", value_ptr->characters);
        }
        fprintf(f_ptr, "\n");
    }
} /* end SE_PrintURN */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintVariableCode
 *
 *-----------------------------------------------------------------------------
 */
const char *
SE_PrintVariableCode
(
    SE_Variable_Code value
)
{
    static char buffer[256];
               /*
                * for enumerator string (or error message)
                */

    switch (value)
    {
        case SE_VARCOD_ACTIVE_STATE_VALUE:
             return "SE_VARCOD_ACTIVE_STATE_VALUE";

        case SE_VARCOD_CLR_COORDINATE_1:
             return "SE_VARCOD_CLR_COORDINATE_1";

        case SE_VARCOD_CLR_COORDINATE_2:
             return "SE_VARCOD_CLR_COORDINATE_2";

        case SE_VARCOD_CLR_COORDINATE_3:
             return "SE_VARCOD_CLR_COORDINATE_3";

        case SE_VARCOD_CLR_INDEX:
             return "SE_VARCOD_CLR_INDEX";

        case SE_VARCOD_CLR_INTENSITY_LEVEL:
             return "SE_VARCOD_CLR_INTENSITY_LEVEL";

        case SE_VARCOD_GEOMETRY_TEXTURE:
             return "SE_VARCOD_GEOMETRY_TEXTURE";

        case SE_VARCOD_HEAT_PRODUCTION:
             return "SE_VARCOD_HEAT_PRODUCTION";

        case SE_VARCOD_LIGHT_SOURCE_ACTIVE:
             return "SE_VARCOD_LIGHT_SOURCE_ACTIVE";

        case SE_VARCOD_LGT_RENDER_PROP_ACTIVE:
             return "SE_VARCOD_LGT_RENDER_PROP_ACTIVE";

        case SE_VARCOD_LGT_RENDER_PROP_CANDELA_VALUE:
             return "SE_VARCOD_LGT_RENDER_PROP_CANDELA_VALUE";

        case SE_VARCOD_LSR_3D_LOCATION_U:
             return "SE_VARCOD_LSR_3D_LOCATION_U";

        case SE_VARCOD_LSR_3D_LOCATION_V:
             return "SE_VARCOD_LSR_3D_LOCATION_V";

        case SE_VARCOD_LSR_3D_LOCATION_W:
             return "SE_VARCOD_LSR_3D_LOCATION_W";

        case SE_VARCOD_POLY_FLAGS_COLLIDIBLE:
             return "SE_VARCOD_POLY_FLAGS_COLLIDIBLE";

        case SE_VARCOD_POLY_FLAGS_HAT_TEST:
             return "SE_VARCOD_POLY_FLAGS_HAT_TEST";

        case SE_VARCOD_POLY_FLAGS_INVISIBLE:
             return "SE_VARCOD_POLY_FLAGS_INVISIBLE";

        case SE_VARCOD_POLY_FLAGS_LASER_RNG_FIND:
             return "SE_VARCOD_POLY_FLAGS_LASER_RNG_FIND";

        case SE_VARCOD_PROPERTY_SET_INDEX:
             return "SE_VARCOD_PROPERTY_SET_INDEX";

        case SE_VARCOD_PROP_TABLE_REF_ON_AXIS:
             return "SE_VARCOD_PROP_TABLE_REF_ON_AXIS";

        case SE_VARCOD_REF_VEC_V0:
             return "SE_VARCOD_REF_VEC_V0";

        case SE_VARCOD_REF_VEC_V1:
             return "SE_VARCOD_REF_VEC_V1";

        case SE_VARCOD_REF_VEC_V2:
             return "SE_VARCOD_REF_VEC_V2";

        case SE_VARCOD_ROTATION_ANGLE:
             return "SE_VARCOD_ROTATION_ANGLE";

        case SE_VARCOD_SCALE_AMOUNT:
             return "SE_VARCOD_SCALE_AMOUNT";

        case SE_VARCOD_SOUND_INSTANCE_ACTIVE:
             return "SE_VARCOD_SOUND_INSTANCE_ACTIVE";

        case SE_VARCOD_TEXTURE_COORD_S:
             return "SE_VARCOD_TEXTURE_COORD_S";

        case SE_VARCOD_TEXTURE_COORD_T:
             return "SE_VARCOD_TEXTURE_COORD_T";

        case SE_VARCOD_TRANSLATION_AMOUNT:
             return "SE_VARCOD_TRANSLATION_AMOUNT";

        case SE_VARCOD_TRANSLUCENCY_VALUE:
             return "SE_VARCOD_TRANSLUCENCY_VALUE";

        default:
             sprintf(buffer,"ERROR - ILLEGAL SE_Variable_Code VALUE (%i)",
                    (int) value);
             break;
    } /* end switch */

    return buffer;
} /* end SE_PrintVariableCode */


/*
 *-----------------------------------------------------------------------------
 *
 * FUNCTION: SE_PrintYIQData
 *
 *-----------------------------------------------------------------------------
 */
void
SE_PrintYIQData
(
    const SE_YIQ_Data *value_ptr,
    const char        *name_ptr,
          SE_Integer_Unsigned  level
)
{
    FILE *f_ptr;

    f_ptr = SE_GetOutFilePtr();
    if (!value_ptr)
    {
        SE_Indent(level, f_ptr);
        if (name_ptr)
            fprintf(f_ptr, "%s is NULL, can't print\n", name_ptr);
        else
            fprintf(f_ptr, "Can't print NULL SE_YIQ_Data\n");
        return;
    }
    if (name_ptr)
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->y: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->y));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->i: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->i));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "%s->q: %s\n", name_ptr, SE_PrintLongFloat
                (value_ptr->q));
    }
    else
    {
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "y: %s\n", SE_PrintLongFloat(value_ptr->y));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "i: %s\n", SE_PrintLongFloat(value_ptr->i));
        SE_Indent(level, f_ptr);
        fprintf(f_ptr, "q: %s\n", SE_PrintLongFloat(value_ptr->q));
    }
} /* end SE_PrintYIQData */
