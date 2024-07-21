import Head from "next/head";
import Container from "react-bootstrap/Container";
import Header from "@/components/Header";
import { useRouter } from "next/router";
import ScatterPlot from "./scatterplot";

export default function Home() {
  const router = useRouter();
  const handleButtonClick = () => {
    router.push('/students');
  }

  return (
    <>
      <Head>
        <title>Studemeter</title>
        <meta name="description" content="Students Focus Monitoring System" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <link rel="icon" href="/favicon.ico" />
      </Head>
      <Container as="main" className="py-4 px-3 mx-auto">
        <Header text="" href="/" />

        <div className="row justify-content-center">
          <div className="col-12 col-lg-6 justify-content-center p-0 border rounded-4">
            
            <div className="bg-light rounded-4">
              <div className="row justify-content-center">
                <div className="col-12 fs-4 text-center my-2">
                  Karim Mohamed
                </div>
                <div className="col-12 mb-2 text-center">
                  <div>
                    <span className="text-primary text-capitalize">Mostly focused</span> from 8:00 AM till now
                  </div>
                </div>
              </div>
            </div>

            <div className="col my-1">
              <ScatterPlot />
            </div>

            <div className="bg-light rounded-4">
              <div className="row justify-content-center">
                <div className="col-12 mb-2">
                  <div className="text-uppercase text-center mt-2 mb-2 fs-6 opacity-50">
                    Time period to display in
                  </div>
                  <div className="row justify-content-center py-2 px-5">
                    <div className="form-check col-12 text-center">
                      <input className="form-check-input" type="radio" name="timePeriod" id="duringClass" checked />
                      <label className="form-check-label text-capitalize" htmlFor="duringClass">
                        During class
                      </label>
                    </div>
                  </div>
                </div>
              </div>
            </div>

            <div className="col-12 mt-4">
              <div className="row justify-content-center">
                <div className="col-auto">
                  <button type="button" onClick={handleButtonClick} className="text-capitalize btn btn-primary rounded-pill">
                    <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" className="bi bi-caret-left-fill" viewBox="0 0 16 16">
                      <path d="m3.86 8.753 5.482 4.796c.646.566 1.658.106 1.658-.753V3.204a1 1 0 0 0-1.659-.753l-5.48 4.796a1 1 0 0 0 0 1.506z" />
                    </svg>
                    Back
                  </button>
                </div>
              </div>
            </div>

          </div>
        </div>
      </Container>
    </>
  );
}
