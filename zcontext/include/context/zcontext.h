
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef CONTEXT_ZCONTEXT_H
#define CONTEXT_ZCONTEXT_H

#if defined(_WIN32_WCE)
typedef int intptr_t;
#endif

#undef CONTEXT_CALLDECL
#if (defined(i386) || defined(__i386__) || defined(__i386) \
     || defined(__i486__) || defined(__i586__) || defined(__i686__) \
     || defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) \
     || defined(__I86__) || defined(__INTEL__) || defined(__IA32__) \
     || defined(_M_IX86) || defined(_I86_)) && defined(BOOST_WINDOWS)
# define CONTEXT_CALLDECL __cdecl
#else
# define CONTEXT_CALLDECL
#endif

typedef void*   zcontext_t;

extern "C" 
intptr_t CONTEXT_CALLDECL jump_zcontext( zcontext_t * ofc, zcontext_t nfc,
                                         intptr_t vp, bool preserve_fpu = false);
extern "C" 
zcontext_t CONTEXT_CALLDECL make_zcontext( void * sp, std::size_t size, void (* fn)( intptr_t) );




#endif // CONTEXT_ZCONTEXT_H

