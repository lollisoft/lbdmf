

#ifndef __LB_INTERFACES_SUB_WXWRAPPER__
#define __LB_INTERFACES_SUB_WXWRAPPER__

/**
 * Forward declarations, needed to use wx peers.
 * A peer is derived from the wrapped companion class.
 */

class lb_wxFrame;


/**
 * Peer interfaces to its wx companions
 */

class lb_I_wxFrame : public lb_I_Unknown,
public lb_I_EventSink
{
public:
	virtual lb_wxFrame* getPeer() = 0;
};

#endif // __LB_INTERFACES_SUB_WXWRAPPER__
