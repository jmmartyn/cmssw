//
// $Id: PATTauCleaner.h,v 1.1 2008/01/16 01:22:39 gpetrucc Exp $
//

#ifndef PhysicsTools_PatAlgos_PATTauCleaner_h
#define PhysicsTools_PatAlgos_PATTauCleaner_h

/**
  \class    PATTauCleaner PATTauCleaner.h "PhysicsTools/PatAlgos/interface/PATTauCleaner.h"
  \brief    Produces pat::Tau's

   The PATTauCleaner produces analysis-level pat::Tau's starting from
   a collection of objects of TauType.

  \author   Steven Lowette, Christophe Delaere
  \version  $Id: PATTauCleaner.h,v 1.1 2008/01/16 01:22:39 gpetrucc Exp $
*/


#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"

#include "PhysicsTools/PatAlgos/interface/CleanerHelper.h"
#include "DataFormats/TauReco/interface/BaseTau.h"
#include <DataFormats/TauReco/interface/PFTau.h>
#include <DataFormats/TauReco/interface/PFTauDiscriminatorByIsolation.h>
#include <DataFormats/TauReco/interface/CaloTau.h>
#include <DataFormats/TauReco/interface/CaloTauDiscriminatorByIsolation.h>

#include "PhysicsTools/Utilities/interface/PtComparator.h"

#include <string>


namespace pat {


  template<typename TauIn, typename TauOut, typename TauTag>
  class PATTauCleaner : public edm::EDProducer {

    public:

      explicit PATTauCleaner(const edm::ParameterSet & iConfig);
      ~PATTauCleaner();

      virtual void produce(edm::Event & iEvent, const edm::EventSetup & iSetup);

    private:
      // configurables
      edm::InputTag tauSrc_;
      edm::InputTag tauDiscSrc_;
      pat::helper::CleanerHelper<TauIn,
                                 TauOut,
                                 std::vector<TauOut>,
                                 GreaterByPt<TauOut> > helper_;

  };

  typedef PATTauCleaner<reco::PFTau,reco::PFTau,reco::PFTauDiscriminatorByIsolation>       PATPFTauCleaner;
  typedef PATTauCleaner<reco::CaloTau,reco::CaloTau,reco::CaloTauDiscriminatorByIsolation> PATCaloTauCleaner;
  typedef PATTauCleaner<reco::PFTau,reco::BaseTau,reco::PFTauDiscriminatorByIsolation>     PATPF2BaseTauCleaner;
  typedef PATTauCleaner<reco::CaloTau,reco::BaseTau,reco::CaloTauDiscriminatorByIsolation> PATCalo2BaseTauCleaner;
}

#endif
