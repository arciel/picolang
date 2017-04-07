
// The picoVal base class.
// This represents data values in a pico
// program. 

// All pico value types inherit from this.
// A picoVal is a tagged union of sorts, and
// can contain one of...
// picoRational, picoChar, picoString, picoList,
// picoLazyList and picoLambda.

// The contained types implement the operators for
// that type. i.e., picoList implements 'get' and 'cons'
// while picoLambda implements 'call'.

// Also, I need to figure out some sort of symbol table
// which stores identifier -> picoval variable maps.

// And figure out how to pass references to lambdas/

#pragma once

// #include <variant>
// no variant support in my g++ yet.
// :sad:
// lets invent a shitty knockoff suited our purposes.
// The types for the variant are fixed.

#include <memory>

#include "picoInt.hpp"
#include "picoChar.hpp"
#include "picoString.hpp"
#include "picoList.hpp"
#include "picoLazyList.hpp"
#include "picoLambda.hpp"

/*
enum class picoTypeTag
{
    Char, Int, String, List, LazyList, Lambda
};
*/
struct picoVal
{
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

