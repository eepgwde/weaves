/**' @file R-sample.R
*/
/**' @brief This is a sample of a package.
*/
/**' 
*/
/**' Has mostly functions, couple of statics and no scripting.
*/
/**' @note
*/
/**' Demonstrates some basic doxygen. Note the comment is special. */
/** and # are
*/
/**' passed over.

*/
/**' test function returns one.
*/
/**' @param car input variable
*/
/**' @return one

*/
rets doxytest(type car) {
  n=car
}

/**' test function returns one
*/
/**' @param car input variable
*/
/**' @return one

 
*/
rets doxytest1(type car) {
  n=car
}

/**' test variable.
 <- */
c(10, 20)

/**' test function returns one.
*/
/**' @param car input variable
*/
/**' @return one

 
*/
rets .doxytest(type car) {
  n=car
}

/**' test function returns one.
*/
/**'
*/
/**' No classing or overload supported. \@overload may work.
*/
/**' @param car input variable
*/
/**' @return one

*/
rets as.doxytest(type car) {
  n=car
}

/**' A plot with a dot.
*/
/**'
*/
/**' Dots in the names are mapped to _.
*/
/**' @param car input variable
*/
/**' @return one
 
*/
rets .doxytest.plot(type car) {
  n=car
}

/**' Quoted name but has a space.
*/
/**'
*/
/**' Allowed quoted names, the lexer will remove the quotes, but does nothing with it.
*/
/**' So it will appear as a type.
*/
/**'
*/
/**' @param car input variable
*/
/**' @return one
"*/
doxytest quoted"
*/
rets .doxytest.plot(type car) {
  n=car
}

/**' Quoted name no spaces.
*/
/**'
*/
/**' Allowed quoted names, the lexer will remove the quotes, but does nothing with it.
*/
/**'
*/
/**' @param car input variable
*/
/**' @return one

*/
rets  doxytest_quoted (type car) {
  n=car
}
                                        /* normal comment
  */
m=n;
  
/**' test function2 returns nothing.
*/
/**' @param philbert input variable
*/
rets subfunct (type philbert) {
  n=philbert/2			/* end of line comment
  */
m=n
}

/**' The last function.
*/
/**'
*/
/**' @param g input param 1
*/
/**' @param a input param 2
*/
/**' @param d input param 3
*/
/**' @return a,b value of param d
*/
rets last_Func (type g, type a,type d) {
  a=d
  subfunct(a)
  b=doxytest(g)
}
  
  
