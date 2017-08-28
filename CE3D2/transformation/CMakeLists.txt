list(APPEND SRC ${CMAKE_CURRENT_LIST_DIR}/ITransformable
                ${CMAKE_CURRENT_LIST_DIR}/LinearTransformation
                ${CMAKE_CURRENT_LIST_DIR}/LinearTransformationChain
                ${CMAKE_CURRENT_LIST_DIR}/MatrixTransformation
                ${CMAKE_CURRENT_LIST_DIR}/Mirror
                ${CMAKE_CURRENT_LIST_DIR}/OrthogonalProjection
                ${CMAKE_CURRENT_LIST_DIR}/Permutation
                ${CMAKE_CURRENT_LIST_DIR}/PermutationVector
                ${CMAKE_CURRENT_LIST_DIR}/Rotation
                ${CMAKE_CURRENT_LIST_DIR}/Scale
                ${CMAKE_CURRENT_LIST_DIR}/Transformation
                ${CMAKE_CURRENT_LIST_DIR}/TransformationChain
                ${CMAKE_CURRENT_LIST_DIR}/Translation)

set(SRC "${SRC}" PARENT_SCOPE)
