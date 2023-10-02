@a = dso_local global <13 x i1> undef, align 1
@b = dso_local global <13 x i1> undef, align 1
@c = dso_local global <13 x i1> undef, align 1

define void @vector_add() {
    %a = load <13 x i1>, ptr @a, align 1
    %b = load <13 x i1>, ptr @b, align 1
    %d = add <13 x i1> %a, %b
    store <13 x i1> %d, ptr @c, align 1
    ret void
}
