//
// Created by lavigne on 10/8/17.
//

/* Include l'include SpiderClient pour t_paquet et la rendre global server/client */
#include <boost/archive/text_iarchive.hpp>

void                                deserialize(t_paquet *data, boost::asio::streambuf &buf)
{
    std::istream                    is(&buf);
    boost::archive::text_iarchive   ar(is);

    ar & data;
}