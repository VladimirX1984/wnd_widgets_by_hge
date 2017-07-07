#pragma once

class ResourceObject;
class Widget;
class WidgetContainer;
class hgeSprite;
class hgeParticleSystem;

#if BOOST

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost;

typedef boost::shared_ptr<ResourceObject> ResRef;
typedef boost::shared_ptr<Widget> WidgetRef;
typedef boost::shared_ptr<WidgetContainer> WidgetContainerRef;
typedef boost::weak_ptr<Widget> WeakWidgetRef;
typedef boost::weak_ptr<WidgetContainer> WeakWidgetContainerRef;
typedef boost::shared_ptr<hgeSprite> HgeSpriteRef;
typedef boost::shared_ptr<hgeParticleSystem> HgePsRef;

using boost::make_shared;
using boost::function;
using boost::enable_shared_from_this;
using boost::dynamic_pointer_cast;
using boost::static_pointer_cast;
using boost::reinterpret_pointer_cast;

#else

#include<memory>
#include <functional>

using namespace std;

typedef std::shared_ptr<ResourceObject> ResRef;
typedef std::shared_ptr<Widget> WidgetRef;
typedef std::shared_ptr<WidgetContainer> WidgetContainerRef;
typedef std::weak_ptr<Widget> WeakWidgetRef;
typedef std::weak_ptr<WidgetContainer> WeakWidgetContainerRef;
typedef std::shared_ptr<hgeSprite> HgeSpriteRef;
typedef std::shared_ptr<hgeParticleSystem> HgePsRef;

using std::make_shared;
using std::tr1::function;
using std::enable_shared_from_this;
using std::dynamic_pointer_cast;
using std::static_pointer_cast;
using std::reinterpret_pointer_cast;

#endif