# About

CE3D2 is a leightweight 3D engine specifically designed for rendering
ASCII-art. Since it's not using heavy graphic pipelines and utilizes CPU only,
the vector arithmetic is very flexible (e.g. transformations not using a
matrix).

## Overview

CE3D2 is grouped into namespaces where each one serves a certain functionality:

- `CE3D2::Models`

  Contains different types of models. Models store vectors that make up your
  mesh.

- `CE3D2::Render`

  Classes for rendering are located here. The most important are
  `CE3D2::Render::TextRenderer` and `CE3D2::Render::TextSurface`.

- `CE3D2::Transformation`

  Contains the transformation system for modifying vectors. E.g.
  `CE3D2::Transformation::Rotation` or `CE3D2::Transformation::Scale`.

The `CE3D2` namespace itself contains some very important types you will use
in nearly every application:

- `CE3D2::Vector`

  The vector class used throughout CE3D2. Special descendants are
  `CE3D2::UnitVector` and `CE3D2::ZeroVector`. For documentation of them refer
  to the
  [Boost documentation](http://www.boost.org/doc/libs/1_60_0/libs/numeric/ublas/doc/index.html).

- `CE3D2::Matrix`

  The matrix class of CE3D2. Special descendants are `CE3D2::IdentityMatrix` and
  `CE3D2::ZeroMatrix`. For documentation of them refer to the
  [Boost documentation](http://www.boost.org/doc/libs/1_60_0/libs/numeric/ublas/doc/index.html).

## Precision

CE3D2 uses `float` precision for vectors and matrices. You can build with better
precision like `double`. To do so change `CE3D2::PrecisionType`.
