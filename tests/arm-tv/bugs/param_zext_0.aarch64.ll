; TEST-ARGS:

define  zeroext i8 @func17(i8 zeroext %0) {
  %2 = lshr i8 %0, 5
  ret i8 %2
}
