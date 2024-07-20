import Head from "next/head";
import Container from "react-bootstrap/Container";
import Header from "@/components/Header";
import Link from "next/link";
import { useRouter } from "next/router";

interface StudentParams {
  id: number;
  name: string;
  isDistracted: boolean;
}

function StudentDiv({ id, name, isDistracted }: StudentParams) {
  return (
    <div className="row mx-1 my-2">
      <div className="col-12">
        <div className={"row justify-content-between p-2 rounded-4 bg-opacity-10 " + (isDistracted ? "bg-secondary" : "bg-primary")}>
          <div className="col-12 fs-4">
            {name}
          </div>
          <div className="col-auto fs-6 text-uppercase fg-primary">
            {isDistracted ?              
              <span className="text-secondary font-weight-bold">Distracted</span>
            : <span className="text-primary">Normal</span>}
          </div>
          <Link href="/history" className="btn btn-sm col-auto rounded-pill fs-6 text-uppercase opacity-50">
            View History
            <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" className="bi bi-caret-right-fill" viewBox="0 0 16 16">
              <path d="m12.14 8.753-5.482 4.796c-.646.566-1.658.106-1.658-.753V3.204a1 1 0 0 1 1.659-.753l5.48 4.796a1 1 0 0 1 0 1.506z" />
            </svg>
          </Link>
        </div>
      </div>
    </div>
  );
}

export default function Home() {
  const router = useRouter();
  const classroomName = "Classroom 1/2";
  const starts = "8:00 AM";
  const ends = "9:30 AM";
  const students = [
    { id: 1, name: "Karim Mohamed", isDistracted: true },
    
  ];

  return (
    <>
      <Head>
        <title>Studemeter</title>
        <meta name="description" content="Students Focus Monitoring System" />
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <link rel="icon" href="/favicon.ico" />
      </Head>
      <Container as="main" className="py-4 px-3 mx-auto">
        <Header text="back" href="/teacher" />

        <div className="row justify-content-center">
          <div className="col-12 col-lg-6 p-0 border rounded-4 bg-light">
            <div className="p-3">
              <div className="fs-4 text-center mb-2">
                {classroomName}
              </div>
              <div className="mb-3 text-center">
                <div className="fs-6">30 Total present students</div>
                <div className="text-secondary">4 Distracted students</div>
              </div>
              <div className="my-scrollable">
                {students.map(student => (
                  <StudentDiv key={student.id} id={student.id} name={student.name} isDistracted={student.isDistracted} />
                ))}
              </div>
              <div className="row text-center mt-3">
                <div className="col-6">
                  <div className="text-uppercase text-muted fs-5">Starts</div>
                  <div className="fs-3">{starts}</div>
                </div>
                <div className="col-6">
                  <div className="text-uppercase text-muted fs-5">Ends</div>
                  <div className="fs-3">{ends}</div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </Container>
    </>
  );
}
