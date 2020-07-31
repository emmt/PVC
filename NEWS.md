# User visible changes in PVC

## 31 juil. 2020

* Vectorized operations in `<pvc-vect.h>`: `pvc_vadd` (addition),
  `pvc_vsub` (subtraction), `pvc_vmul` (multiplication), `pvc_vdiv`
  (division), `pvc_vmin` (minimum), `pvc_vmax` (maximum), `pvc_vzero`
  (zero-fill), `pvc_vload` (load from aligned memory), `pvc_vloadu`
  (load from unaligned memory), `pvc_vstore` (store from aligned
  memory) and `pvc_vstoreu` (store to unalign memory).

* Headers `<pvc-clamp.h>`, `<pvc-min.h>` and `<pvc-max.h>` have been
  suppressed in favor of `<pvc-math.h>`.
