list(APPEND SRC ${CMAKE_CURRENT_LIST_DIR}/ITransformable
                ${CMAKE_CURRENT_LIST_DIR}/Transformation
                ${CMAKE_CURRENT_LIST_DIR}/LinearTransformation
                ${CMAKE_CURRENT_LIST_DIR}/MatrixTransformation
                ${CMAKE_CURRENT_LIST_DIR}/Rotation
                ${CMAKE_CURRENT_LIST_DIR}/Scale
                ${CMAKE_CURRENT_LIST_DIR}/OrthogonalProjection)

set(SRC "${SRC}" PARENT_SCOPE)
