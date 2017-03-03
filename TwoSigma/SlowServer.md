## Reference:

* http://blog.scoutapp.com/articles/2014/07/31/slow_server_flow_chart
* https://my.bluehost.com/cgi/help/481
* https://mediatemple.net/community/products/dv/204403944/why-is-my-website-slow
* https://developer.yahoo.com/performance/rules.html

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

#### Enable compression 
The time it takes to transfer an HTTP request and response across the network can be significantly reduced by decisions made by front-end engineers. It's true that the end-user's bandwidth speed, Internet service provider, proximity to peering exchange points, etc. are beyond the control of the development team. But there are other variables that affect response times. Compression reduces response times by reducing the size of the HTTP response. Gzip is the most popular and effective compression method at this time. There are known issues with browsers and proxies that may cause a mismatch in what the browser expects and what it receives with regard to compressed content. Fortunately, these edge cases are dwindling as the use of older browsers drops off. The Apache modules help out by adding appropriate Vary response headers automatically.Servers choose what to gzip based on file type, but are typically too limited in what they decide to compress. Most web sites gzip their HTML documents. It's also worthwhile to gzip your scripts and stylesheets, but many web sites miss this opportunity. In fact, it's worthwhile to compress any text response including XML and JSON. Image and PDF files should not be gzipped because they are already compressed. Trying to gzip them not only wastes CPU but can potentially increase file sizes.Gzipping as many file types as possible is an easy way to reduce page weight and accelerate the user experience.

#### Reduce redirects 
Each time a page redirects to another page, your visitor faces additional time waiting for the HTTP request-response cycle to complete. For example, if your mobile redirect pattern looks like this: "example.com -> www.example.com -> m.example.com -> m.example.com/home," each of those two additional redirects makes your page load slower.

#### Minimize HTTP Requests 
80% of the end-user response time is spent on the front-end. Most of this time is tied up in downloading all the components in the page: images, stylesheets, scripts, Flash, etc. Reducing the number of components in turn reduces the number of HTTP requests required to render the page. This is the key to faster pages.One way to reduce the number of components in the page is to simplify the page's design. But is there a way to build pages with richer content while also achieving fast response times? Here are some techniques for reducing the number of HTTP requests, while still supporting rich page designs.Combined files are a way to reduce the number of HTTP requests by combining all scripts into a single script, and similarly combining all CSS into a single stylesheet. Combining files is more challenging when the scripts and stylesheets vary from page to page, but making this part of your release process improves response times.

#### Use a Content Delivery Network 
The user's proximity to your web server has an impact on response times. Deploying your content across multiple, geographically dispersed servers will make your pages load faster from the user's perspective. But where should you start? As a first step to implementing geographically dispersed content, don't attempt to redesign your web application to work in a distributed architecture. Depending on the application, changing the architecture could include daunting tasks such as synchronizing session state and replicating database transactions across server locations. Attempts to reduce the distance between users and your content could be delayed by, or never pass, this application architecture step.Remember that 80-90% of the end-user response time is spent downloading all the components in the page: images, stylesheets, scripts, Flash, etc. This is the Performance Golden Rule. Rather than starting with the difficult task of redesigning your application architecture, it's better to first disperse your static content. This not only achieves a bigger reduction in response times, but it's easier thanks to content delivery networks.A content delivery network (CDN) is a collection of web servers distributed across multiple locations to deliver content more efficiently to users. The server selected for delivering content to a specific user is typically based on a measure of network proximity. For example, the server with the fewest network hops or the server with the quickest response time is chosen.

Use CDNs (content delivery networks) to offload traffic from your site. Ensure it is cost justified and then choose which content is most suitable. Most CDNs leverage DNS (Domain Name Services or Domain Name Servers) to serve content on your site’s behalf. CDNs help offload traffic spikes and are often economical ways to scale parts of a site’s traffic. CDNs are a fast and simple way to offset spikiness of traffic as well as traffic growth in general. Make sure you perform a cost-benefit analysis and monitor the CDN usage.CDNs are a collection of computers, called nodes or edge servers, connected via a network, called a backbone, that have duplicate copies of their customers’ data or content (images, Web pages, and so on) on them. By strategically placing edge servers on different Tier 1 networks and employing a myriad of technologies and algorithms the CDN can direct requests to nodes that are optimally suited to respond.This optimization could be based on such things as the fewest network hops, highest availability, or fewest requests.The focus of this optimization is most often the reduction of response times as perceived by the end user, requesting person, or service.The benefit of using a CDN in front of our own blog server is that the CDN takes all the requests (possibly hundreds or thousands per hour) and only requests from our server when checking for updated cache.This requires you to purchase fewer servers, less power, and smaller amounts of bandwidth, as well as fewer people required to maintain that infrastructure.This aid in scale, availability, and response time isn’t free—it typically comes at a premium to your public peering (Internet peering) traffic costs.Whether you have dynamic or static pages on your site, consider adding a CDN into the mix of caches.This layer provides the benefit of faster delivery, typically very high availability, and less traffic on your site’s servers.

#### Put Stylesheets at the Top 
While researching performance at Yahoo!, we discovered that moving stylesheets to the document HEAD makes pages appear to be loading faster. This is because putting stylesheets in the HEAD allows the page to render progressively.Front-end engineers that care about performance want a page to load progressively; that is, we want the browser to display whatever content it has as soon as possible. This is especially important for pages with a lot of content and for users on slower Internet connections. The importance of giving users visual feedback, such as progress indicators, has been well researched and documented. In our case the HTML page is the progress indicator! When the browser loads the page progressively the header, the navigation bar, the logo at the top, etc. all serve as visual feedback for the user who is waiting for the page. This improves the overall user experience.The problem with putting stylesheets near the bottom of the document is that it prohibits progressive rendering in many browsers, including Internet Explorer. These browsers block rendering to avoid having to redraw elements of the page if their styles change. The user is stuck viewing a blank white page.The HTML specification clearly states that stylesheets are to be included in the HEAD of the page: "Unlike A, [LINK] may only appear in the HEAD section of a document, although it may appear any number of times." Neither of the alternatives, the blank white screen or flash of unstyled content, are worth the risk. The optimal solution is to follow the HTML specification and load your stylesheets in the document HEAD.

#### Put Scripts at the Bottom 
The problem caused by scripts is that they block parallel downloads. The HTTP/1.1 specification suggests that browsers download no more than two components in parallel per hostname. If you serve your images from multiple hostnames, you can get more than two downloads to occur in parallel. While a script is downloading, however, the browser won't start any other downloads, even on different hostnames.In some situations it's not easy to move scripts to the bottom. If, for example, the script uses document.write to insert part of the page's content, it can't be moved lower in the page. There might also be scoping issues. In many cases, there are ways to workaround these situations.An alternative suggestion that often comes up is to use deferred scripts. The DEFER attribute indicates that the script does not contain document.write, and is a clue to browsers that they can continue rendering. Unfortunately, Firefox doesn't support the DEFER attribute. In Internet Explorer, the script may be deferred, but not as much as desired. If a script can be deferred, it can also be moved to the bottom of the page. That will make your web pages load faster.

#### Make JavaScript and CSS External 
Many of these performance rules deal with how external components are managed. However, before these considerations arise you should ask a more basic question: Should JavaScript and CSS be contained in external files, or inlined in the page itself?Using external files in the real world generally produces faster pages because the JavaScript and CSS files are cached by the browser. JavaScript and CSS that are inlined in HTML documents get downloaded every time the HTML document is requested. This reduces the number of HTTP requests that are needed, but increases the size of the HTML document. On the other hand, if the JavaScript and CSS are in external files cached by the browser, the size of the HTML document is reduced without increasing the number of HTTP requests.The key factor, then, is the frequency with which external JavaScript and CSS components are cached relative to the number of HTML documents requested. This factor, although difficult to quantify, can be gauged using various metrics. If users on your site have multiple page views per session and many of your pages re-use the same scripts and stylesheets, there is a greater potential benefit from cached external files.Many web sites fall in the middle of these metrics. For these sites, the best solution generally is to deploy the JavaScript and CSS as external files. The only exception where inlining is preferable is with home pages, such as Yahoo!'s front page and My Yahoo!. Home pages that have few (perhaps only one) page view per session may find that inlining JavaScript and CSS results in faster end-user response times.For front pages that are typically the first of many page views, there are techniques that leverage the reduction of HTTP requests that inlining provides, as well as the caching benefits achieved through using external files. One such technique is to inline JavaScript and CSS in the front page, but dynamically download the external files after the page has finished loading. Subsequent pages would reference the external files that should already be in the browser's cache.

#### Reduce DNS Lookups 
The Domain Name System (DNS) maps hostnames to IP addresses, just as phonebooks map people's names to their phone numbers. When you type www.yahoo.com into your browser, a DNS resolver contacted by the browser returns that server's IP address. DNS has a cost. It typically takes 20-120 milliseconds for DNS to lookup the IP address for a given hostname. The browser can't download anything from this hostname until the DNS lookup is completed.

DNS lookups are cached for better performance. This caching can occur on a special caching server, maintained by the user's ISP or local area network, but there is also caching that occurs on the individual user's computer. The DNS information remains in the operating system's DNS cache (the "DNS Client service" on Microsoft Windows). Most browsers have their own caches, separate from the operating system's cache. As long as the browser keeps a DNS record in its own cache, it doesn't bother the operating system with a request for the record.

Internet Explorer caches DNS lookups for 30 minutes by default, as specified by the DnsCacheTimeout registry setting. Firefox caches DNS lookups for 1 minute, controlled by the network.dnsCacheExpiration configuration setting. (Fasterfox changes this to 1 hour.)

When the client's DNS cache is empty (for both the browser and the operating system), the number of DNS lookups is equal to the number of unique hostnames in the web page. This includes the hostnames used in the page's URL, images, script files, stylesheets, Flash objects, etc. Reducing the number of unique hostnames reduces the number of DNS lookups.

Reducing the number of unique hostnames has the potential to reduce the amount of parallel downloading that takes place in the page. Avoiding DNS lookups cuts response times, but reducing parallel downloads may increase response times. My guideline is to split these components across at least two but no more than four hostnames. This results in a good compromise between reducing DNS lookups and allowing a high degree of parallel downloads.
  
This process of translating domains into IP addresses is made quicker by caching on many levels, including the browser, computer operating system, Internet service provider, and so on. However, in our world where pages can have hundreds or thousands of objects, many from different domains, small milliseconds of time can add up to something noticeable to the customer.Browsers take advantage of the fact that almost all Web pages are comprised of many different objects (images, JavaScript files, css files, and so on) by having the ability to download multiple objects through simultaneous connections. Browsers limit the maximum number of simultaneous persistent connections per server or proxy.Every distinct domain that serves one or more objects for a Web page requires a DNS lookup either from cache or out to a DNS name server.

#### Reduce Objects Where Possible 
Web pages consist of many different objects (HTML, CSS, images, JavaScript, and so on), which allows our browsers to download them somewhat independently and often in parallel. One of the easiest ways to improve Web page performance and thus increase your scalability (fewer objects to serve per page means your servers can serve more pages) is to reduce the number of objects on a page.The biggest offenders on most pages are graphical objects such as pictures and images.

#### Minify JavaScript and CSS

Minification is the practice of removing unnecessary characters from code to reduce its size thereby improving load times. When code is minified all comments are removed, as well as unneeded white space characters (space, newline, and tab). In the case of JavaScript, this improves response time performance because the size of the downloaded file is reduced. Two popular tools for minifying JavaScript code are JSMin and YUI Compressor. The YUI compressor can also minify CSS.

Obfuscation is an alternative optimization that can be applied to source code. It's more complex than minification and thus more likely to generate bugs as a result of the obfuscation step itself. In a survey of ten top U.S. web sites, minification achieved a 21% size reduction versus 25% for obfuscation. Although obfuscation has a higher size reduction, minifying JavaScript is less risky.

In addition to minifying external scripts and styles, inlined \<script\> and \<style\> blocks can and should also be minified. Even if you gzip your scripts and styles, minifying them will still reduce the size by 5% or more. As the use and size of JavaScript and CSS increases, so will the savings gained by minifying your code.

#### Make Ajax Cacheable
One of the cited benefits of Ajax is that it provides instantaneous feedback to the user because it requests information asynchronously from the backend web server. However, using Ajax is no guarantee that the user won't be twiddling his thumbs waiting for those asynchronous JavaScript and XML responses to return. In many applications, whether or not the user is kept waiting depends on how Ajax is used. For example, in a web-based email client the user will be kept waiting for the results of an Ajax request to find all the email messages that match their search criteria. It's important to remember that "asynchronous" does not imply "instantaneous".

To improve performance, it's important to optimize these Ajax responses. The most important way to improve the performance of Ajax is to make the responses cacheable.

#### Minify CSS, JavaScript, and HTML 
By optimizing your code (including removing spaces, commas, and other unnecessary characters), you can dramatically increase your page speed. 

## Application Problems

#### No/Poor Load Distribution
Poor load distribution can cause slow response times by incorrectly assigning new site visitors to bogged-down servers instead of others with cycles to spare. If too many people are on the same server, they’re going to experience problems, even if the overall system is well under capacity. 

#### Lack of caching or inefficient caching. 
In many situations, application or perimeter caching can improve Web services performance. Caching-related issues that can significantly affect Web services performance include failure to use caching for Web methods, caching too much data, caching inappropriate data, and using inappropriate expiration settings.

Caches are not the be-all end-all solution, but once you have decided to use a cache, there are a few things you need to consider:
*	 Caches are a fixed size
*	 Distributed caching is a non-trivial problem

Caches hold stateful objects, unlike pools, which hold stateless objects. For example, imagine a pool as the registers at a supermarket. When you’re ready to check out, you go to whichever register is free – it doesn’t matter which one you get.  Pools contain stateless objects, meaning it doesn’t matter which connection you get – all connections are equal, but caches contain stateful objects because you go to a cache looking for a specific piece of data. 

Because caches are stateful, you must configure them to a finite size so as not to exhaust memory. When the cache is full, then the cache must respond based on its configuration. For example, it might remove the least recently used object from the cache to make room for the new object. This means that sometimes the requested object may no longer be in the cache, resulting in a “miss.” A miss typically results in a database call to find the requested object. The higher your miss ratio, therefore, the less you’re taking advantage of the performance benefits of the cache. It’s important to optimize your cache settings carefully, so that you maintain a good “hit ratio” without exhausting all the memory.

Distributed caching. If you have multiple servers in a tier all writing to their own caches, how do they stay in sync? If you do not configure the caches to be distributed, then they won’t. Depending on which server you hit, your results may vary (which is usually a bad thing). Most modern caches support a distributed paradigm so that when a cache is updated it will propagate its changes to other members in the cache. But depending on the number of cached nodes and the consistency of data you require, this can be expensive. Consistency refers to the integrity of your data at a point in time: if one cache node has one value for an object and another node has a different value then the two cache nodes are said to be inconsistent. On the loose end of the spectrum, caches can be “eventually consistent,” meaning that your application can tolerate short periods of time when the caches on different nodes do not have the same values. 

#### Inefficient state management. 
Inefficient state management design in Web services can lead to scalability bottlenecks because the server becomes overloaded with state information that it must maintain on a per-user basis. Common pitfalls for Web services state management include using stateful Web methods, using cookie containerbased state management, and choosing an inappropriate state store. The most scalable Web services maintain no state.

#### Misuse of threads. 
It is easy to misuse threads. For example, you might create threads on a per-request basis or you might write code that misuses the thread pool. Also, unnecessarily implementing a Web method asynchronously can cause more worker threads to be used and blocked, which affects the performance of the Web server.
On the client side, consumers of Web services have the option of calling Web services asynchronously or synchronously. Your code should call a Web service asynchronously only when you want to avoid blocking the client while a Web service call is in progress. If you are not careful, you can use a greater number of worker and I/O threads, which negatively affects performance. It is also slower to call a service asynchronously; therefore, you should avoid doing so unless your client application needs to do something else while the service is invoked.

#### Concurrency
Code deadlocks occur when two or more threads each possess the lock for a resource the other thread needs to complete its task and neither thread is willing to give up the lock that it has already obtained. In a synchronized code block, a thread must first obtain the lock for the code block before executing that code and, while it has the lock, no other thread will be permitted to enter the code block. When your application has a deadlock in it, your JVM will eventually exhaust all or most of its threads. The application will appear to be accomplishing less and less work, but the CPU utilization of the machine on which the application is running will appear underutilized. Additionally, if you request a thread dump you will see reports of deadlocked threads.

If your application is running in an application server or web container, it will have a thread pool configured to control how many requests your application can concurrently process. The server receives a request by a socket listener, places it in an execution queue, and then returns to listen for the next request to arrive on the socket. The execution queue is serviced by a thread pool. When a thread is available in the thread pool, a request is removed from the execution queue and passed to a thread for processing. The thread executes the appropriate business transaction in your application code. When the thread completes processing the thread is returned to the thread pool and will be available to process another request. 

The configuration of the size of that thread pool is going to be of paramount importance to the performance of your application. If the thread pool is sized too small then your requests are going to wait (much like you would while on hold for your cable provider) but if the thread pool is sized too large then too many threads are going to execute concurrently and take all of the machine’s processing resources. When there are too many threads and the machine spends too much time context switching between threads, the threads will be “starved” of CPU cycles and will take longer to complete. You have a finite number of cores in your CPU and if threads need computing power (they aren’t waiting) then there’s only so much processing power to go around. The behavior of your application will dictate the optimal size of your thread pools.

When a thread pool is sized too small then you will see the thread pool utilization (number of active threads divided by the total number of threads) at or near 100%, requests backing up in the execution queue, and the CPU underutilized. The reason is that the application has used all available threads but is not using all of the processing capabilities available to it on the machine. And because it cannot process requests fast enough, requests back up. When a thread pool is sized too large then you will see a moderately used thread pool, very few if any pending requests in the execution queue, but the CPU utilization will be at or near 100%. The reason for this is that the application has more threads than the machine is equipped to process.

Troubleshooting thread pool sizing problems is actually a lot easier than the other performance challenges presented in this eBook. The key is to look at two metrics: : 
* Thread pool utilization 
* CPU utilization 

If your thread pool utilization is high (at or near 100% with pending requests) and your CPU utilization is moderate then your thread pool is probably configured too small. If your thread pool utilization is moderate, but your CPU utilization is high then your thread pool is probably configured too large.

The way to avoid thread pool misconfigurations is to tune the thread pool. This sounds easy in theory, but it’s time consuming in practice. In short, you want to size your pool large enough to properly utilize your machine’s processing resources but not large enough to saturate them. But there’s a complication: if your application accesses external resources, such as a database, your application should be configured to send enough load to those external resources to use them effectively, but not saturate them. 

The way to avoid thread pool misconfigurations is to tune the thread pool. This sounds easy in theory, but it’s time consuming in practice. In short, you want to size your pool large enough to properly utilize your machine’s processing resources but not large enough to saturate them. But there’s a complication: if your application accesses external resources, such as a database, your application should be configured to send enough load to those external resources to use them effectively, but not saturate them. 




#### Serialization
The amount of serialization that is required for your Web method requests and responses is a significant factor for overall Web services performance. Serialization overhead affects network congestion, memory consumption, and processor utilization. To help keep the serialization overhead to a minimum:

* Reduce serialization.
* Reduce round trips.
* Consider XML compression.

Reducing round trips to a Web service reduces the number of times that messages need to cross serialization boundaries. This helps reduce the overall serialization cost incurred. Design options that help to reduce round trips include the following:
Use message-based interaction with a message-based programming model, rather than an RPC style that requires multiple object interactions to complete a single logical unit of work.
In some cases, split a large payload into multiple calls to the Web service. Consider making the calls in parallel using asynchronous invocation instead of in series. This does not technically reduce the total number of round trips, but in essence the client waits for only a single round trip.

## Database Problems
* Indexing : Make sure appropriate indexes is built for fast access. Analyze the frequently-used queries and examine the query plan when it is executed (e.g. use "explain" for MySQL). Check whether appropriate index exist and being used.
* Data De-normalization : Table join is an expensive operation and should be reduced as much as possible. One technique is to de-normalize the data such that certain information is repeated in different tables.
* DB Replication : For typical web application where the read/write ratio is high, it will be useful to maintain multiple read-only replicas so that read access workload can be spread across. For example, in a 1 master/N slaves case, all update goes to master DB which send a change log to the replicas. However, there will be a time lag for replication.
* Table Partitioning : You can partition vertically or horizontally. Vertical partitioning is about putting different DB tables into different machines or moving some columns (rarely access attributes) to a different table. Of course, for query performance reason, tables that are joined together inside a query need to reside in the same DB.Horizontally partitioning is about moving different rows within a table into a separated DB. For example, we can partition the rows according to user id. Locality of reference is very important, we should put the rows (from different tables) of the same user together in the same machine if these information will be access together.
* Transaction Processing : Avoid mixing OLAP (query intensive) and OLTP (update intensive) operations within the same DB. In the OLTP system, avoid using long running database transaction and choose the isolation level appropriately. A typical technique is to use optimistic business transaction. Under this scheme, a long running business transaction is executed outside a database transaction. Data containing a version stamp is read outside the database trsnaction. When the user commits the business transaction, a database transaction is started at that time, the lastest version stamp of the corresponding records is re-read from the DB to make sure it is the same as the previous read (which means the data is not modified since the last read). Is so, the changes is pushed to the DB and transaction is commited (with the version stamp advanced). In case the version stamp is mismatched, the DB transaction as well as the business transaction is aborted.


#### Database structure is not well defined/normalized
This is probably known to everybody that the database tables should be properly normalized as this is part of every DBMS course at graduation level. If the tables are not properly designed and normalized, anomalies set in.

#### Proper caching is not in place
Many applications make use of temporary caches on the application server to store the reference data or frequently accessed data as memory is less of an issue than the time with new generation servers.

#### Number of rows in the table too large
If the table itself has too much of data then the queries will take time to execute. Partitioning a table into multiple tables is recommended in these situations. For example: If a table has employee records of 1000000 employees then it could be split into 5 small tables each having 200000 rows. The advantage is we know beforehand in which smaller table to look for a particular employee code as the division of large table can be done on the employee id column.

####  Connections are not being pooled
If connections are not pooled then the each time a new connection is requested for a request to database. Maintaining a connection pool is much better than creating and destroying the connection for executing every SQL query.
Connections not closed/returned to pool in case of exceptions: When an exception occurs while performing database operations, it ought to be caught. Usually catching the exception is not the issue because SQLException is a checked exception but closing the connection is something that most of the times is left out. If the connection is not released, the same connection cannot be used for any other purpose till the connection is timed out.

 The number of connections to your database controls how many concurrent queries can be executed against it. If there are too few connections in the pool then you’ll have a bottleneck in your application, increasing response times and angering end users.
 
 Database connections are pooled for several reasons:
•	 Database connections are relatively expensive to create, so rather than create them on the fly we opt to create them beforehand and use them whenever we need to access the database.
•	 The database is a shared resource so it makes sense to create a pool of connections and share them across all business transactions.
•	 The database connection pool limits the amount of load that you can send to your database.

The first two points make sense because we want to pre-create expensive resources and share them across our application. The last point, however, might seem counterintuitive. We pool connections to reduce load on the database because otherwise we might saturate the database with too much load and bring it to a screeching halt. The point is that not only do you want to pool your connections, but you also need to configure the size of the pool correctly.

If you do not have enough connections, then business transactions will be forced to wait for a connection to become available before they can continue processing. If you have too many connections, however, then you might be sending too much load to the database and then all business transactions across all application servers will suffer from slow database performance. The trick is finding the middle ground.

The main symptoms of a database connection pool that is sized too small are increased response time across multiple business transactions, with the majority of those business transactions waiting on a Datasource.getConnection() call, in conjunction with low resource utilization on the database machine. At first glance this will look like a database problem, but the low resource utilization reveals that the database is, in fact, under-utilized, which means the bottleneck is occurring in the application.

The symptoms of a database connection pool that is sized too large are increased response time across multiple business transactions, with the majority of those business transactions waiting on the response from queries, and high resource utilization in the database machine. 

So while the external symptoms between these two conditions are the same, the internal symptoms are the opposite. In order to correctly identify the problem, you need to find out where your application is waiting on the database (for a connection to the database or on the execution of a query) and what the health of the database is.


The impact of a misconfigured database connection pool rates an 8 on my scale because the performance impact will be observable by your users. The fix is simple but will require time and effort: use load testing and a performance analysis tool to find the optimal value for the size of your database connection pool, and then make the configuration change.







