/* Zeo - Z/Geometry and optics computation library.
 * Copyright (C) 2005 Tomomichi Sugihara (Zhidao)
 *
 * zeo_prim_cone - primitive 3D shapes: cone.
 */

#ifndef __ZEO_PRIM_CONE_H__
#define __ZEO_PRIM_CONE_H__

/* NOTE: never include this header file in user programs. */

__BEGIN_DECLS

/* ********************************************************** */
/* CLASS: zCone3D
 * 3D cone class
 * ********************************************************** */

typedef struct{
  zVec3D center, vert;
  double radius;
  int div;
} zCone3D;

#define zCone3DCenter(c)        ( &(c)->center )
#define zCone3DVert(c)          ( &(c)->vert )
#define zCone3DRadius(c)        (c)->radius
#define zCone3DDiv(c)           (c)->div

#define zCone3DSetCenter(c,p)   zVec3DCopy( p, zCone3DCenter(c) )
#define zCone3DSetVert(c,v)     zVec3DCopy( v, zCone3DVert(c) )
#define zCone3DSetRadius(c,r)   ( zCone3DRadius(c) = (r) )
#define zCone3DSetDiv(c,d)      ( zCone3DDiv(c) = (d) )

/*! \brief initialization, creation and copy of 3D cone.
 *
 * zCone3DInit() initializes a 3D cone \a cone by setting both the center on the
 * base and the vertex for the original point and radius of the base for zero.
 *
 * zCone3DCreate() creates a 3D cone whose center point on the base is \a c,
 * vertex is \a v, and radius of the base is \a r.
 * \a div is the number of division for polyhedral approximation.
 * When zero is given for \a div, ZEO_PRIM_DEFAULT_DIV is set instead.
 *
 * zCone3DCopy() copies a 3D cone \a src to the other \a dest.
 * \return
 * Each of zCone3DInit() and zCone3DCreate() returns a pointer \a cone.
 * zCone3DCopy() returns a pointer the copied \a dest.
 */
__EXPORT zCone3D *zCone3DCreate(zCone3D *cone, zVec3D *c, zVec3D *v, double r, int div);
__EXPORT zCone3D *zCone3DInit(zCone3D *cone);
__EXPORT zCone3D *zCone3DCopy(zCone3D *src, zCone3D *dest);
__EXPORT zCone3D *zCone3DMirror(zCone3D *src, zCone3D *dest, zAxis axis);

/*! \brief transformation of a 3D cone.
 *
 * zCone3DXfer() transforms a 3D cone \a src by a transformation frame \a f,
 * and puts it into \a dest.
 *
 * zCone3DXferInv() transforms \a src by the inverse transformation frame of
 * \a f and puts it into \a dest.
 * \return
 * Each of zCone3DXfer() and zCone3DXferInv() returns a pointer \a dest.
 */
__EXPORT zCone3D *zCone3DXfer(zCone3D *src, zFrame3D *f, zCone3D *dest);
__EXPORT zCone3D *zCone3DXferInv(zCone3D *src, zFrame3D *f, zCone3D *dest);

/*! \brief check if a point is inside of a cone.
 *
 * zCone3DPointIsInside() checks if a 3D point \a p is inside of a 3D cone \a cone.
 * \return
 * zCone3DPointIsInside() returns the true value when \a p is inside of \a cone,
 * or the false value otherwise.
 */
__EXPORT double zCone3DClosest(zCone3D *cone, zVec3D *p, zVec3D *cp);
__EXPORT double zCone3DPointDist(zCone3D *cone, zVec3D *p);
__EXPORT bool zCone3DPointIsInside(zCone3D *cone, zVec3D *p, bool rim);

/*! \brief axis vector, height and volume of 3D cone.
 *
 * zCone3DAxis() calculates the axis vector of a 3D cone \a cone; the axis
 * from the center point on the base to the vertex.
 *
 * zCone3DHeight() calculates the height from the base to the vertex of a 3D cone \a cone.
 *
 * zCone3DVolume() calculates the volume of a 3D cone \a cone.
 * \return
 * zCone3DAxis() returns a pointer \a axis.
 * zCone3DHeight() returns the height calculated.
 * zCone3DVolume() returns the volume calculated.
 */
#define zCone3DAxis(c,a) zVec3DSub( zCone3DVert(c), zCone3DCenter(c), a )
__EXPORT double zCone3DHeight(zCone3D *cone);
__EXPORT double zCone3DVolume(zCone3D *cone);

__EXPORT zVec3D *zCone3DBarycenter(zCone3D *cone, zVec3D *c);
__EXPORT zMat3D *zCone3DInertia(zCone3D *cone, zMat3D *inertia);

/*! \brief convert cone to polyhedron.
 *
 * zCone3DToPH() converts a cone \a cone to a polyhedron \a ph as a polygon model.
 * It approximately divides the side face into rectangles by the stored number of division.
 * \a ph should be initialized in advance.
 * \return
 * zCone3DToPH() returns a pointer \a ph.
 * \sa
 * zSphere3DToPH, zSphere3DToPH, zCyl3DToPH, zCyl3DToPHDRC
 */
__EXPORT zPH3D *zCone3DToPH(zCone3D *cone, zPH3D *ph);

/* METHOD:
 * zCone3DFRead, zCone3DRead, zCone3DFWrite, zCone3DWrite,
 * - input/output of 3D cone.
 *
 * 'zCone3DFRead()' reads the information of a 3D cone
 * from the current position of the file 'fp', and creates
 * the new cone 'cone'.
 * An acceptable data file format is as follows.
 * #
 *  center: <x> <y> <z>
 *  vert: <x> <y> <z>
 *  radius: <r>
 *  div: <div>
 * #
 * Each bracketed value must be substituted for a real number.
 * 'zCone3DRead()' reads the information for 'cone'
 * simply from the standard input.
 * The field div is skippable.
 * #
 * 'zCone3DFWrite()' writes the information of 'cone'
 * to the current position of the file 'fp' in the same format
 * with the above. 'zCone3DWrite()' writes the information
 * of 'cone' simply to the standard out.
 * [RETURN VALUE]
 * Each of 'zCone3DFRead()' and 'zCone3DRead()' returns
 * a pointer 'cone'.
 * #
 * Neither 'zCone3DFWrite()' nor 'zCone3DWrite()' returns
 * any values.
 */
__EXPORT zCone3D *zCone3DFRead(FILE *fp, zCone3D *cone);
#define zCone3DRead(c) zCone3DFRead( stdin, (c) )
__EXPORT void zCone3DFWrite(FILE *fp, zCone3D *cone);
#define zCone3DWrite(c) zCone3DFWrite( stdout, (c) )

/* methods for abstraction */
extern zPrimCom zprim_cone3d_com;

__END_DECLS

#endif /* __ZEO_PRIM_CONE_H__ */
