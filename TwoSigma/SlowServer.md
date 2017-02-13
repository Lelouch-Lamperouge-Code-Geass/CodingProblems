## Reference:

* http://blog.scoutapp.com/articles/2014/07/31/slow_server_flow_chart
* https://my.bluehost.com/cgi/help/481
* https://mediatemple.net/community/products/dv/204403944/why-is-my-website-slow

## Overview
There are many reasons a website may be slow.

* A huge spike in Additional Traffic.
* A Dynamic Site without caching.
* Extremely Large or non-optimized graphics.
* Extremely Large or non-optimized database.
* Large amount of calls to external websites (twitter, facebook, youtube, etc...)
* Connectivity issues

All of these issue fall into three categories: Traffic issues, Site optimization, and configuration issues.

## Network Problem : : Is it everyone or just my local area?
Sometimes a website loads slowly not because the server is slow but because your network connection to the server is slow or intermittent at one of the network "hops" between your location and the server. The problem may not even be with your local Internet Service Provider. There are usually 5-20 different Internet Service Providers between your local computer and the server.

One of the best ways to test for network problems is to run a __traceroute__ from your computer to the server. A traceroute will show all of the network hops between you and the server, and how long your connection took to go through each one. It will also show network timeouts (with ***).

Another quick and easy test for network problems is to use a proxy server to load your web page. A proxy server loads your website from a third-party location and should hopefully bypass local network problems. 

What to do if you've identified a network problem: If you haven't already, run a __traceroute__. If the timeout occurs right away, check your local network and router. If it occurs at your local Internet Service Provider or later down the line, you should contact your Internet Service Provider. Even if they aren't the direct cause of the problem, they may be able to re-route traffic to your website through a different network path.
You also have the option to simply wait out the problem. Most Internet Service Providers will have their connection up and running again within a few hours.

## Page-specific problems
You should also test whether the slowness is limited to specific web pages, or is universal for all pages on the server. Many modern web pages contain dozens of complex elements which drag down the overall load time of the web page, and would do the same no matter how powerful or fast the host server.

* Reduce DNS Lookups: This process of translating domains into IP addresses is made quicker by caching on many levels, including the browser, computer operating system, Internet service provider, and so on. However, in our world where pages can have hundreds or thousands of objects, many from different domains, small milliseconds of time can add up to something noticeable to the customer.Browsers take advantage of the fact that almost all Web pages are comprised of many different objects (images, JavaScript files, css files, and so on) by having the ability to download multiple objects through simultaneous connections. Browsers limit the maximum number of simultaneous persistent connections per server or proxy.Every distinct domain that serves one or more objects for a Web page requires a DNS lookup either from cache or out to a DNS name server.
* Reduce Objects Where Possible : Web pages consist of many different objects (HTML, CSS, images, JavaScript, and so on), which allows our browsers to download them somewhat independently and often in parallel. One of the easiest ways to improve Web page performance and thus increase your scalability (fewer objects to serve per page means your servers can serve more pages) is to reduce the number of objects on a page.The biggest offenders on most pages are graphical objects such as pictures and images.
* Leverage Content Delivery Networks: Use CDNs (content delivery networks) to offload traffic from your site. Ensure it is cost justified and then choose which content is most suitable. Most CDNs leverage DNS (Domain Name Services or Domain Name Servers) to serve content on your site’s behalf. CDNs help offload traffic spikes and are often economical ways to scale parts of a site’s traffic. CDNs are a fast and simple way to offset spikiness of traffic as well as traffic growth in general. Make sure you perform a cost-benefit analysis and monitor the CDN usage.CDNs are a collection of computers, called nodes or edge servers, connected via a network, called a backbone, that have duplicate copies of their customers’ data or content (images, Web pages, and so on) on them. By strategically placing edge servers on different Tier 1 networks and employing a myriad of technologies and algorithms the CDN can direct requests to nodes that are optimally suited to respond.This optimization could be based on such things as the fewest network hops, highest availability, or fewest requests.The focus of this optimization is most often the reduction of response times as perceived by the end user, requesting person, or service.The benefit of using a CDN in front of our own blog server is that the CDN takes all the requests (possibly hundreds or thousands per hour) and only requests from our server when checking for updated cache.This requires you to purchase fewer servers, less power, and smaller amounts of bandwidth, as well as fewer people required to maintain that infrastructure.This aid in scale, availability, and response time isn’t free—it typically comes at a premium to your public peering (Internet peering) traffic costs.Whether you have dynamic or static pages on your site, consider adding a CDN into the mix of caches.This layer provides the benefit of faster delivery, typically very high availability, and less traffic on your site’s servers.



## Database Problems








