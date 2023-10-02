@a = dso_local global <16 x i11> undef, align 1
@b = dso_local global <16 x i11> undef, align 1
@c = dso_local global <16 x i11> undef, align 1

define void @vector_add() {
    %a = load <16 x i11>, ptr @a, align 1
    %b = load <16 x i11>, ptr @b, align 1
    %d = add <16 x i11> %a, %b
    store <16 x i11> %d, ptr @c, align 1
    ret void
}
