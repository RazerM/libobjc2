#ifndef __LIBOBJC_RUNTIME_H_INCLUDED__
#define __LIBOBJC_RUNTIME_H_INCLUDED__

// If __LEGACY_GNU_MODE__ is defined then we include the old GNU runtime header
// instead of this one
#ifndef __OBJC_LEGACY_GNU_MODE__
#define __GNUSTEP_RUNTIME__

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include "Availability.h"

#ifdef ERROR_UNSUPPORTED_RUNTIME_FUNCTIONS
#	define OBJC_GNU_RUNTIME_UNSUPPORTED(x) \
		__attribute__((error(x " not supported by this runtime")))
#else
#	define OBJC_GNU_RUNTIME_UNSUPPORTED(x)
#endif

// Undo GNUstep substitutions
#ifdef class_setVersion 
#undef class_setVersion
#endif
#ifdef class_getClassMethod
#undef class_getClassMethod
#endif
#ifdef objc_getClass
#undef objc_getClass
#endif
#ifdef objc_lookUpClass
#undef objc_lookUpClass
#endif

typedef struct objc_ivar* Ivar;

// Don't redefine these types if the old GNU header was included first.
#ifndef __objc_INCLUDE_GNU
typedef const struct objc_selector *SEL;

typedef struct objc_class *Class;

typedef struct objc_object
{
	Class isa;
} *id;

struct objc_super {
	id receiver;
#	if !defined(__cplusplus)  &&  !__OBJC2__
	Class class;
#	else
	Class super_class;
#	endif
};

typedef id (*IMP)(id, SEL, ...);
typedef struct objc_method *Method;

#	ifdef STRICT_APPLE_COMPATIBILITY
typedef signed char BOOL;
#	else
#		ifdef __vxwords
typedef  int BOOL
#		else
typedef unsigned char BOOL;
#		endif
#	endif

#else
// Method in the GNU runtime is a struct, Method_t is the pointer
#	define Method Method_t
#endif // __objc_INCLUDE_GNU



typedef void *objc_property_t;
#ifdef __OBJC__
@class Protocol;
#else
typedef struct objc_protocol Protocol;
#endif

#ifndef YES
#define YES ((BOOL)1)
#endif
#ifndef NO 
#define NO ((BOOL)0)
#endif

#ifdef __GNUC
#define _OBJC_NULL_PTR __null
#elif defined(__cplusplus)
#define _OBJC_NULL_PTR 0
#else
#define _OBJC_NULL_PTR ((void*)0)
#endif

#ifndef nil
#define nil ((id)_OBJC_NULL_PTR)
#endif

#ifndef Nil
#define Nil ((Class)_OBJC_NULL_PTR)
#endif

BOOL class_addIvar(Class cls,
                   const char *name,
                   size_t size,
                   uint8_t alignment,
                   const char *types);

BOOL class_addMethod(Class cls, SEL name, IMP imp, const char *types);

BOOL class_addProtocol(Class cls, Protocol *protocol);

BOOL class_conformsToProtocol(Class cls, Protocol *protocol);

Ivar * class_copyIvarList(Class cls, unsigned int *outCount);

Method * class_copyMethodList(Class cls, unsigned int *outCount);

OBJC_GNU_RUNTIME_UNSUPPORTED("Property introspection")
objc_property_t * class_copyPropertyList(Class cls, unsigned int *outCount);

Protocol ** class_copyProtocolList(Class cls, unsigned int *outCount);

id class_createInstance(Class cls, size_t extraBytes);

Method class_getClassMethod(Class aClass, SEL aSelector);

Ivar class_getClassVariable(Class cls, const char* name);

Method class_getInstanceMethod(Class aClass, SEL aSelector);

size_t class_getInstanceSize(Class cls);

Ivar class_getInstanceVariable(Class cls, const char* name);

const char *class_getIvarLayout(Class cls);

IMP class_getMethodImplementation(Class cls, SEL name);

IMP class_getMethodImplementation_stret(Class cls, SEL name);

const char * class_getName(Class cls);

OBJC_GNU_RUNTIME_UNSUPPORTED("Property introspection")
objc_property_t class_getProperty(Class cls, const char *name);

Class class_getSuperclass(Class cls);

int class_getVersion(Class theClass);

OBJC_GNU_RUNTIME_UNSUPPORTED("Weak instance variables")
const char *class_getWeakIvarLayout(Class cls);

BOOL class_isMetaClass(Class cls);

IMP class_replaceMethod(Class cls, SEL name, IMP imp, const char *types);

BOOL class_respondsToSelector(Class cls, SEL sel);

void class_setIvarLayout(Class cls, const char *layout);

__attribute__((deprecated))
Class class_setSuperclass(Class cls, Class newSuper);

void class_setVersion(Class theClass, int version);

OBJC_GNU_RUNTIME_UNSUPPORTED("Weak instance variables")
void class_setWeakIvarLayout(Class cls, const char *layout);

const char * ivar_getName(Ivar ivar);

ptrdiff_t ivar_getOffset(Ivar ivar);

const char * ivar_getTypeEncoding(Ivar ivar);

char * method_copyArgumentType(Method method, unsigned int index);

char * method_copyReturnType(Method method);

void method_exchangeImplementations(Method m1, Method m2);

void method_getArgumentType(Method method, unsigned int index, char *dst, size_t dst_len);

IMP method_getImplementation(Method method);

SEL method_getName(Method method);

unsigned method_getNumberOfArguments(Method method);

void method_getReturnType(Method method, char *dst, size_t dst_len);

const char * method_getTypeEncoding(Method method);

IMP method_setImplementation(Method method, IMP imp);

Class objc_allocateClassPair(Class superclass, const char *name, size_t extraBytes);

void objc_disposeClassPair(Class cls);

id objc_getClass(const char *name);

int objc_getClassList(Class *buffer, int bufferLen);

id objc_getMetaClass(const char *name);

id objc_getRequiredClass(const char *name);

id objc_lookUpClass(const char *name);

Class objc_allocateClassPair(Class superclass, const char *name, size_t extraBytes);

Protocol *objc_getProtocol(const char *name);

void objc_registerClassPair(Class cls);

void *object_getIndexedIvars(id obj);

// FIXME: The GNU runtime has a version of this which omits the size parameter
//id object_copy(id obj, size_t size);

id object_dispose(id obj);

Class object_getClass(id obj);

const char *object_getClassName(id obj);

IMP objc_msg_lookup(id, SEL);
IMP objc_msg_lookup_super(struct objc_super*, SEL);

OBJC_GNU_RUNTIME_UNSUPPORTED("Protocol introspection")
BOOL protocol_conformsToProtocol(Protocol *p, Protocol *other);

OBJC_GNU_RUNTIME_UNSUPPORTED("Protocol introspection")
struct objc_method_description *protocol_copyMethodDescriptionList(Protocol *p,
	BOOL isRequiredMethod, BOOL isInstanceMethod, unsigned int *count);

OBJC_GNU_RUNTIME_UNSUPPORTED("Protocol introspection")
objc_property_t *protocol_copyPropertyList(Protocol *p, unsigned int *count);

OBJC_GNU_RUNTIME_UNSUPPORTED("Protocol introspection")
Protocol **protocol_copyProtocolList(Protocol *p, unsigned int *count);

OBJC_GNU_RUNTIME_UNSUPPORTED("Protocol introspection")
struct objc_method_description protocol_getMethodDescription(Protocol *p,
	SEL aSel, BOOL isRequiredMethod, BOOL isInstanceMethod);

const char *protocol_getName(Protocol *p);

OBJC_GNU_RUNTIME_UNSUPPORTED("Protocol introspection")
objc_property_t protocol_getProperty(Protocol *p, const char *name,
	BOOL isRequiredProperty, BOOL isInstanceProperty);

BOOL protocol_isEqual(Protocol *p, Protocol *other);

#else
#include "runtime-legacy.h"
#endif // __LEGACY_GNU_MODE__

/**
 * The objc_slot structure is used to permit safe IMP caching.  It is returned
 * by the new lookup APIs.  When you cache an IMP, you should store a copy of
 * the version field and a pointer to the slot. 
 *
 * The slot version is guaranteed never to be 0.  When updating a cache, you
 * should use code of the following form:
 *
 * 1) version = 0;
 * 2) slot->cachedFor = receiver->isa;
 * 3) slot_cache = slot;
 * 4) version = slot->version;
 *
 * The runtime guarantees that the version in any cachable slot will never be
 * 0.  This should ensure that, if the version and cache pointer mismatch, the
 * next access will cause a cache miss.  
 *
 * When using a cached slot, you should compare the owner pointer to the isa
 * pointer of the receiver and the message and the version of the slot to your
 * cached version.
 */
struct objc_slot
{
	/** The class to which this slot is attached (used internally).  */
	Class owner;
	/** The class for which this slot was cached.  Note that this can be
	 * modified by different cache owners, in different threads.  Doing so may
	 * cause some cache misses, but if different methods are sending messages
	 * to the same object and sharing a cached slot then it may also improve
	 * cache hits.  Profiling is probably required here. */
	Class cachedFor;
	/** The type encoding for the method identified by this slot. */
	char *types;
	/** The current version.  This changes if the method changes or if a
	 * subclass overrides this method, potentially invalidating this cache. */
	int version;
	/** The method pointer for this method. */
	IMP method;
} OBJC_NONPORTABLE;
/**
 * New ABI lookup function.  Receiver may be modified during lookup or proxy
 * forwarding and the sender may affect how lookup occurs.
 */
struct objc_slot *objc_msg_lookup_sender(id *receiver, SEL selector, id sender)
	OBJC_NONPORTABLE;
/**
 * Hook provided to allow libraries to support fast proxies.
 */
id (*objc_proxy_lookup)(id receiver, SEL op) OBJC_NONPORTABLE;
/**
 * New message lookup hook.  This returns a slot, rather than an IMP.  The
 * version should be set to 0 to disable caching.
 */
struct objc_slot *(*objc_msg_forward3)(id receiver, SEL op) OBJC_NONPORTABLE;

/**
 * Runtime hook for unhandled exceptions.  This is called if an exception is
 * not caught.
 */
void (*__objc_unhandled_exception)(id);

// Global self so that self is a valid symbol everywhere.  Will be replaced by
// a real self in an inner scope if there is one.
static const id self = nil;
// This uses a GCC extension, but the is no good way of doing it otherwise.
#define objc_msgSend(theReceiver, theSelector, ...) \
({\
	id __receiver = theReceiver;\
	SEL op = theSelector;\
	objc_msg_lookup_sender(&__receiver, op, self)(__receiver, op, ## __VA_ARGS__);\
})

#define objc_msgSendSuper(super, op, ...) objc_msg_lookup_super(super, op)(super->receiver, op, ## __VA_ARGS__)

#endif // __LIBOBJC_RUNTIME_H_INCLUDED__