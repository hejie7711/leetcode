Cutelyst（Qt/C++ Web框架）第一个版本发布咯！

> 原文链接 http://dantti.wordpress.com/2014/02/11/cutelyst-the-qtc-web-framework-just-got-its-first-version-released/

Three months ago Custelyst was started,

it was somehow a proof of concept to see if I could build something that could be used in the real world, but the more I progressed on getting all the pieces together the happier with the overall result I got. And the initial result is here today!

I have made a few benchmarks comparing some simple pages delivery using Django (python) and Perl Catalyst, and overall the time to first byte was around 3 times faster than both, comparing RAM usage it was like 2MB vs 50MB from the Perl version and 20MB of the Python one, the CPU time was also much smaller if compared to both which probably means it could handle more requests, but this isn’t a completely fair benchmark (as always) because there are several other things to measure…

Below I’ll try to clarify some doubts raised from my last post and what makes this new Web Framework unique:

But there is already QDjango and Tufao…

I didn’t know about these ones when I first started Cutelyst, but after taking a look at them, both misses a templating system (or integration with one), I also didn’t like the way one would register actions to be dispatched, IMO the way it’s done in Cutelyst is easier and nicer. And they doesn’t count with WSGI integration, they have their own HTTP parser/server. I also didn’t like looking at code :P

Why not DJango or any other well established framework out there?….

Apart from QDjango and Tufao there are no other (AFAIK) Qt based frameworks, there are indeed some C++ ones that I knew before but I didn’t like the way of doing things there, in fact when I started with Perl Catalyst I really liked how it was written. So in short I don’t know well enough other languages and I have no plans wasting my time learning other languages, I’d rather try to master at least one (although I know I’m far from it).

What’s in this release?

Glad you asked (duh!)
Production ready integration with uWSGI, meaning Cutelyst has a uWSGI plugin that will load your application (which will also be a plugin), and thus thanks to uWSGI it will have out of the box support for FastCGI, HTTP(s), uWSGI (protocol) and probably some other.
ClearSilver templates integration, this templating system is written in C and it’s amazingly fast, but it’s also incredible limited to what you can do in the view.
Grantlee (Django) templates integration, it’s used in KDE PIM to allow for easy templating of HTML, it’s slower than ClearSilver but offers much more fexibilities on your views, and since it’s also written in Qt the introspection comes for free.
Complete Path dispatcher, which means if you Port a Perl Catalyst Application that was using Path actions it will work as expected. This dispatcher matches an url to a Q_INVOKABLE method depending on it’s signature, The Catalyst Chained dispatcher is not implemented yet.
Session plugin, easy to use way of persisting data across requests, right now it’s done with a QSettings file, but integration with Redis and MongoDB are planned.
Authentication plugin, allowing you to authenticate your users using different Realms/stores, currently a StoreMinimal is implemented which can be used mostly for testing purposes (ie on the code you add your users)
StaticSimple plugin, allows for serving static content reducing the complexity of serving static content while developing your app.
If you are concerned about API/ABI stability I don’t promise it just right now it’s almost stable, probably 0.2 or 0.3 versions will have a promised stable API.

And yes, I have just put it on production http://serial.igloobox.com.br is running it right now (but the site is user restricted).

My plans now is to setup cutelyst.org with docs and examples, as well as writing a web blog, bug tracker and wiki based on it.

Have fun!

Download
