@a = dso_local global <16 x i8> undef, align 1
@b = dso_local global <16 x i8> undef, align 1
@c = dso_local global <16 x i8> undef, align 1

define void @vector_add_16_8() {
    %a = load <16 x i8>, ptr @a, align 1
    %b = load <16 x i8>, ptr @b, align 1
    %d = add <16 x i8> %a, %b
    store <16 x i8> %d, ptr @c, align 1
    ret void
}
