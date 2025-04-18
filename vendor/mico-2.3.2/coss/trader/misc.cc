#include "misc.h"

#include "CosTrading.h"
#include "trader_main.h"

/**************************************************************
 *
 * TraderComponents
 *
 **************************************************************/
TraderComponents::TraderComponents( Trader *_trader ) : MICO_SCOPE(CosTrading,TraderComponents_skel)()
{
  m_pTrader = _trader;
}

CosTrading::Lookup_ptr TraderComponents::lookup_if()
{
  return m_pTrader->lookup_if();
}

CosTrading::Register_ptr TraderComponents::register_if()
{
  return m_pTrader->register_if();
}

CosTrading::Link_ptr TraderComponents::link_if()
{
  return m_pTrader->link_if();
}

CosTrading::Proxy_ptr TraderComponents::proxy_if()
{
  return m_pTrader->proxy_if();
}

CosTrading::Admin_ptr TraderComponents::admin_if()
{
  return CosTrading::Admin::_nil();
}

/**************************************************************
 *
 * SupportAttributes
 *
 **************************************************************/

SupportAttributes::SupportAttributes( Trader* _trader )
//    : CosTrading::SupportAttributes()
{
  m_pTrader3 = _trader;
}
  
CORBA::Boolean SupportAttributes::supports_modifiable_properties()
{
  return false;
}

CORBA::Boolean SupportAttributes::supports_dynamic_properties()
{
  return false;
}

CORBA::Boolean SupportAttributes::supports_proxy_offers()
{
  return false;
}

CosTrading::TypeRepository_ptr SupportAttributes::type_repos()
{
  return m_pTrader3->typeRepository();
}

/**************************************************************
 *
 * ImportAttributes
 *
 **************************************************************/

ImportAttributes::ImportAttributes( Trader *_trader )
//: CosTrading::ImportAttributes()
{
  m_pTrader2 = _trader;
}
  
CORBA::ULong ImportAttributes::def_search_card()
{
  return m_pTrader2->defSearchCard();
}

CORBA::ULong ImportAttributes::max_search_card()
{
  return m_pTrader2->maxSearchCard();
}

CORBA::ULong ImportAttributes::def_match_card()
{
  return m_pTrader2->defMatchCard();
}

CORBA::ULong ImportAttributes::max_match_card()
{
  return m_pTrader2->maxMatchCard();
}

CORBA::ULong ImportAttributes::def_return_card()
{
  return m_pTrader2->defReturnCard();
}

CORBA::ULong ImportAttributes::max_return_card()
{
  return m_pTrader2->maxReturnCard();
}

CORBA::ULong ImportAttributes::max_list()
{
  return m_pTrader2->maxList();
}

CORBA::ULong ImportAttributes::def_hop_count()
{
  return m_pTrader2->defHopCount();
}

CORBA::ULong ImportAttributes::max_hop_count()
{
  return m_pTrader2->maxHopCount();
}

CosTrading::FollowOption ImportAttributes::def_follow_policy()
{
  return m_pTrader2->defLinkFollowPolicy();
}

CosTrading::FollowOption ImportAttributes::max_follow_policy()
{
  return m_pTrader2->maxLinkFollowPolicy();
}

/**************************************************************
 *
 * LinkAttributes
 *
 **************************************************************/

LinkAttributes::LinkAttributes( Trader *_trader )
{
  m_pTrader5 = _trader;
}

CosTrading::FollowOption LinkAttributes::max_link_follow_policy()
{
  return m_pTrader5->maxLinkFollowPolicy();
}





